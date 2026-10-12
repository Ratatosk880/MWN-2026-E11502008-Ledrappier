#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/internet-module.h"
#include "ns3/point-to-point-module.h"
#include "ns3/applications-module.h"
#include <fstream>
#include <vector>

using namespace ns3;

NS_LOG_COMPONENT_DEFINE ("XR3GPPTrafficModel");

// Application générant le trafic XR/Cloud Gaming selon 3GPP TR 26.926
class XrTrafficApplication : public Application
{
public:
  XrTrafficApplication () : m_socket (0), m_running (false), m_packetsSent (0) {}
  virtual ~XrTrafficApplication () { m_socket = 0; }

  void Setup (Address ip, uint16_t port, double fps, double meanFrameBytes, double stdFrameBytes)
  {
    m_peer = ip;
    m_port = port;
    m_frameInterval = Seconds (1.0 / fps); // Période de trame (ex: 16.66 ms pour 60 fps)
    m_maxPayloadSize = 1460; // Segmentation MTU (1500 B - 40 B IP/UDP)
    m_intraBurstIat = MicroSeconds (200); // 0.2 ms entre paquets d'une rafale (Annexe B)

    // Distribution gaussienne tronquée pour la taille de trame (Clause 6.5.3 / Annexe B)
    m_frameSizeRng = CreateObject<NormalRandomVariable> ();
    m_frameSizeRng->SetAttribute ("Mean", DoubleValue (meanFrameBytes));
    m_frameSizeRng->SetAttribute ("Variance", DoubleValue (stdFrameBytes * stdFrameBytes));
    m_minFrameBytes = meanFrameBytes * 0.5;
    m_maxFrameBytes = meanFrameBytes * 1.5;
  }

private:
  virtual void StartApplication (void)
  {
    m_running = true;
    m_socket = Socket::CreateSocket (GetNode (), UdpSocketFactory::GetTypeId ());
    m_socket->Connect (InetSocketAddress (Ipv4Address::ConvertFrom (m_peer), m_port));
    ScheduleNextFrame ();
  }

  virtual void StopApplication (void)
  {
    m_running = false;
    Simulator::Cancel (m_sendEvent);
    if (m_socket)
      {
        m_socket->Close ();
      }
  }

  void ScheduleNextFrame (void)
  {
    if (m_running)
      {
        // Tirage de la taille de trame
        double frameSize = m_frameSizeRng->GetValue ();
        if (frameSize < m_minFrameBytes) frameSize = m_minFrameBytes;
        if (frameSize > m_maxFrameBytes) frameSize = m_maxFrameBytes;

        uint32_t totalBytes = static_cast<uint32_t> (frameSize);

        // Découpage en paquets MTU
        std::vector<uint32_t> burstPackets;
        while (totalBytes > m_maxPayloadSize)
          {
            burstPackets.push_back (m_maxPayloadSize);
            totalBytes -= m_maxPayloadSize;
          }
        if (totalBytes > 0)
          {
            burstPackets.push_back (totalBytes);
          }

        // Planification de l'envoi de la rafale
        SendBurstPacket (burstPackets, 0);

        // Prochaine trame
        m_sendEvent = Simulator::Schedule (m_frameInterval, &XrTrafficApplication::ScheduleNextFrame, this);
      }
  }

  void SendBurstPacket (std::vector<uint32_t> burstPackets, size_t index)
  {
    if (!m_running || index >= burstPackets.size ())
      {
        return;
      }

    Ptr<Packet> packet = Create<Packet> (burstPackets[index]);
    m_socket->Send (packet);
    m_packetsSent++;

    if (index + 1 < burstPackets.size ())
      {
        Simulator::Schedule (m_intraBurstIat, &XrTrafficApplication::SendBurstPacket, this, burstPackets, index + 1);
      }
  }

  Ptr<Socket> m_socket;
  Address m_peer;
  uint16_t m_port;
  bool m_running;
  uint32_t m_packetsSent;
  Time m_frameInterval;
  Time m_intraBurstIat;
  uint32_t m_maxPayloadSize;
  double m_minFrameBytes;
  double m_maxFrameBytes;
  Ptr<NormalRandomVariable> m_frameSizeRng;
  EventId m_sendEvent;
};

// Traçage pour les distributions
std::ofstream g_txLog;
Time g_lastTxTime = Seconds (0);

void TxTrace (Ptr<const Packet> packet)
{
  Time now = Simulator::Now ();
  double interArrivalMs = (g_lastTxTime.GetSeconds () == 0) ? 0.0 : (now - g_lastTxTime).GetSeconds () * 1000.0;
  g_lastTxTime = now;

  // Taille totale au niveau IP (+28 octets UDP+IP si on compte depuis le niveau payload)
  uint32_t totalPacketSize = packet->GetSize () + 28;
  g_txLog << now.GetSeconds () << "\t" << totalPacketSize << "\t" << interArrivalMs << std::endl;
}

int main (int argc, char *argv[])
{
  CommandLine cmd (__FILE__);
  cmd.Parse (argc, argv);

  Time::SetResolution (Time::NS);

  NodeContainer nodes;
  nodes.Create (2);

  PointToPointHelper p2p;
  p2p.SetDeviceAttribute ("DataRate", StringValue ("100Mbps"));
  p2p.SetChannelAttribute ("Delay", StringValue ("2ms"));

  NetDeviceContainer devices = p2p.Install (nodes);

  InternetStackHelper stack;
  stack.Install (nodes);

  Ipv4AddressHelper address;
  address.SetBase ("10.1.1.0", "255.255.255.0");
  Ipv4InterfaceContainer interfaces = address.Assign (devices);

  uint16_t port = 8080;
  PacketSinkHelper sink ("ns3::UdpSocketFactory", InetSocketAddress (Ipv4Address::GetAny (), port));
  ApplicationContainer sinkApp = sink.Install (nodes.Get (1));
  sinkApp.Start (Seconds (0.0));
  sinkApp.Stop (Seconds (10.0));

  // Instanciation du modèle 3GPP TR 26.926 (60 fps, trame moyenne 25 KB, ecart-type 5 KB)
  Ptr<XrTrafficApplication> xrApp = CreateObject<XrTrafficApplication> ();
  xrApp->Setup (interfaces.GetAddress (1), port, 60.0, 25000.0, 5000.0);
  nodes.Get (0)->AddApplication (xrApp);
  xrApp->SetStartTime (Seconds (1.0));
  xrApp->SetStopTime (Seconds (10.0));

  // Trace PCAP
  p2p.EnablePcap ("results/a2_xr_traffic", devices.Get (0), true);

  // Journalisation
  g_txLog.open ("results/traffic_stats.txt");
  g_txLog << "Timestamp_s\tPacketSize_B\tInterArrival_ms" << std::endl;

  Config::ConnectWithoutContext ("/NodeList/0/DeviceList/*/$ns3::PointToPointNetDevice/MacTx", MakeCallback (&TxTrace));

  Simulator::Stop (Seconds (10.0));
  Simulator::Run ();
  Simulator::Destroy ();

  g_txLog.close ();
  return 0;
}
