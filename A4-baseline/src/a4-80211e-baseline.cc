#include "ns3/applications-module.h"
#include "ns3/core-module.h"
#include "ns3/internet-module.h"
#include "ns3/mobility-module.h"
#include "ns3/network-module.h"
#include "ns3/wifi-module.h"

#include <cmath>
#include <iostream>
#include <string>
#include <vector>

using namespace ns3;

// Application UDP à arrivées de Poisson exactes (inter-arrivées exponentielles)
class PoissonUdpApp : public Application
{
  public:
    PoissonUdpApp() = default;
    void Setup(Address peer, uint32_t pktSize, double rateBps, uint8_t tos)
    {
        m_peer = peer;
        m_pktSize = pktSize;
        m_rateBps = rateBps;
        m_tos = tos;
    }

  private:
    void StartApplication() override
    {
        m_running = true;
        if (!m_socket)
        {
            m_socket = Socket::CreateSocket(GetNode(), UdpSocketFactory::GetTypeId());
            m_socket->SetIpTos(m_tos);
            m_socket->Bind();
            m_socket->Connect(m_peer);
        }
        m_expVar = CreateObject<ExponentialRandomVariable>();
        double meanInterArrival = (m_pktSize * 8.0) / m_rateBps;
        m_expVar->SetAttribute("Mean", DoubleValue(meanInterArrival));
        ScheduleNext();
    }

    void StopApplication() override
    {
        m_running = false;
        if (m_sendEvent.IsPending())
        {
            Simulator::Cancel(m_sendEvent);
        }
        if (m_socket)
        {
            m_socket->Close();
        }
    }

    void ScheduleNext()
    {
        if (m_running && m_rateBps > 0.0)
        {
            Time next = Seconds(m_expVar->GetValue());
            m_sendEvent = Simulator::Schedule(next, &PoissonUdpApp::SendPacket, this);
        }
    }

    void SendPacket()
    {
        Ptr<Packet> pkt = Create<Packet>(m_pktSize);
        m_socket->Send(pkt);
        ScheduleNext();
    }

    Ptr<Socket> m_socket;
    Address m_peer;
    uint32_t m_pktSize{512};
    double m_rateBps{0.0};
    uint8_t m_tos{0};
    bool m_running{false};
    EventId m_sendEvent;
    Ptr<ExponentialRandomVariable> m_expVar;
};

int
main(int argc, char* argv[])
{
    std::string scenario = "fig8"; // "fig8" ou "fig9"
    double offeredPerAcMbps = 6.0; // Utilisé pour fig8 (total par AC sur 3 STAs)
    uint32_t nStas = 3;            // Utilisé pour fig9 (1..16)
    double perStaAcMbps = 1.0;     // Charge par AC et par STA pour fig9
    double simTime = 10.0;         // Durée de mesure (s)
    double warmup = 1.0;           // Temps de chauffe (s)
    uint32_t seed = 1;
    uint32_t run = 1;

    CommandLine cmd(__FILE__);
    cmd.AddValue("scenario", "fig8 or fig9", scenario);
    cmd.AddValue("offeredPerAcMbps", "Total offered load per AC in Mb/s (fig8)", offeredPerAcMbps);
    cmd.AddValue("nStas", "Number of transmitting STAs (fig9)", nStas);
    cmd.AddValue("perStaAcMbps", "Offered load per AC per STA in Mb/s (fig9)", perStaAcMbps);
    cmd.AddValue("simTime", "Measurement duration in seconds", simTime);
    cmd.AddValue("seed", "RNG seed", seed);
    cmd.AddValue("run", "RNG run", run);
    cmd.Parse(argc, argv);

    if (scenario == "fig8")
    {
        nStas = 3;
    }

    RngSeedManager::SetSeed(seed);
    RngSeedManager::SetRun(run);

    // Désactivation RTS/CTS et Fragmentation
    Config::SetDefault("ns3::WifiRemoteStationManager::RtsCtsThreshold", UintegerValue(999999));
    Config::SetDefault("ns3::WifiRemoteStationManager::FragmentationThreshold",
                       UintegerValue(2346));

    NodeContainer apNode;
    apNode.Create(1);
    NodeContainer staNodes;
    staNodes.Create(nStas);

    // PHY 802.11a 5 GHz, Data 24 Mb/s, Control 6 Mb/s
    YansWifiChannelHelper channel = YansWifiChannelHelper::Default();
    YansWifiPhyHelper phy;
    phy.SetChannel(channel.Create());

    WifiHelper wifi;
    wifi.SetStandard(WIFI_STANDARD_80211a);
    wifi.SetRemoteStationManager("ns3::ConstantRateWifiManager",
                                 "DataMode",
                                 StringValue("OfdmRate24Mbps"),
                                 "ControlMode",
                                 StringValue("OfdmRate6Mbps"));

    WifiMacHelper mac;
    Ssid ssid = Ssid("80211e-baseline");

    mac.SetType("ns3::StaWifiMac",
                "Ssid",
                SsidValue(ssid),
                "QosSupported",
                BooleanValue(true));
    NetDeviceContainer staDevices = wifi.Install(phy, mac, staNodes);

    mac.SetType("ns3::ApWifiMac",
                "Ssid",
                SsidValue(ssid),
                "QosSupported",
                BooleanValue(true),
                "EnableBeaconJitter",
                BooleanValue(false));
    NetDeviceContainer apDevice = wifi.Install(phy, mac, apNode);

    // Paramètres EDCA exacts de la Table 1 (IEEE 802.11e/D5.0 pour 802.11a)
    // TXOPlimit = 0 => 1 trame par TXOP
    auto setEdca = [](NetDeviceContainer& devs,
                      AcIndex ac,
                      uint8_t aifsn,
                      uint32_t minCw,
                      uint32_t maxCw,
                      Time txopLimit) {
        for (uint32_t i = 0; i < devs.GetN(); ++i)
        {
            Ptr<WifiNetDevice> wifiDev = DynamicCast<WifiNetDevice>(devs.Get(i));
            Ptr<QosTxop> edca = wifiDev->GetMac()->GetQosTxop(ac);
            edca->SetAifsn(aifsn, 0);
            edca->SetMinCw(minCw, 0);
            edca->SetMaxCw(maxCw, 0);
            edca->SetTxopLimit(txopLimit, 0);
        }
    };

    for (auto* devs : {&apDevice, &staDevices})
    {
        setEdca(*devs, AC_VO, 2, 3, 7, MicroSeconds(0));
        setEdca(*devs, AC_VI, 2, 7, 15, MicroSeconds(0));
        setEdca(*devs, AC_BE, 3, 15, 1023, MicroSeconds(0));
        setEdca(*devs, AC_BK, 7, 15, 1023, MicroSeconds(0));
    }

    // Mobilité : statique, AP au centre (0,0), STAs sur un cercle de rayon 10 m
    MobilityHelper mobility;
    Ptr<ListPositionAllocator> posAlloc = CreateObject<ListPositionAllocator>();
    posAlloc->Add(Vector(0.0, 0.0, 0.0));
    const double radius = 10.0;
    for (uint32_t i = 0; i < nStas; ++i)
    {
        double angle = 2.0 * M_PI * i / nStas;
        posAlloc->Add(Vector(radius * std::cos(angle), radius * std::sin(angle), 0.0));
    }
    mobility.SetPositionAllocator(posAlloc);
    mobility.SetMobilityModel("ns3::ConstantPositionMobilityModel");
    mobility.Install(apNode);
    mobility.Install(staNodes);

    InternetStackHelper stack;
    stack.Install(apNode);
    stack.Install(staNodes);

    Ipv4AddressHelper address;
    address.SetBase("10.1.1.0", "255.255.255.0");
    Ipv4InterfaceContainer apInterface = address.Assign(apDevice);
    Ipv4InterfaceContainer staInterfaces = address.Assign(staDevices);

    // Mapping IP TOS -> 4 ACs (VO, VI, BE, BK)
    const uint8_t tosValues[4] = {0xC0, 0x80, 0x00, 0x20};
    const uint32_t pktSize = 512;

    std::vector<std::vector<Ptr<PacketSink>>> sinks(4);
    uint16_t basePort = 5000;

    for (uint32_t i = 0; i < nStas; ++i)
    {
        for (uint32_t ac = 0; ac < 4; ++ac)
        {
            uint16_t port = basePort + i * 10 + ac;
            Ptr<Node> sender = (scenario == "fig8") ? apNode.Get(0) : staNodes.Get(i);
            Ptr<Node> receiver = (scenario == "fig8") ? staNodes.Get(i) : apNode.Get(0);
            Ipv4Address dstIp =
                (scenario == "fig8") ? staInterfaces.GetAddress(i) : apInterface.GetAddress(0);

            PacketSinkHelper sinkHelper("ns3::UdpSocketFactory",
                                        InetSocketAddress(Ipv4Address::GetAny(), port));
            ApplicationContainer sinkApp = sinkHelper.Install(receiver);
            sinkApp.Start(Seconds(0.0));
            sinkApp.Stop(Seconds(warmup + simTime + 0.5));
            sinks[ac].push_back(DynamicCast<PacketSink>(sinkApp.Get(0)));

            double streamRateBps = (scenario == "fig8")
                                       ? (offeredPerAcMbps * 1e6 / nStas)
                                       : (perStaAcMbps * 1e6);

            Ptr<PoissonUdpApp> app = CreateObject<PoissonUdpApp>();
            app->Setup(InetSocketAddress(dstIp, port), pktSize, streamRateBps, tosValues[ac]);
            sender->AddApplication(app);
            app->SetStartTime(Seconds(warmup));
            app->SetStopTime(Seconds(warmup + simTime));
        }
    }

    Simulator::Stop(Seconds(warmup + simTime + 0.5));
    Simulator::Run();

    double thrMbps[4] = {0.0, 0.0, 0.0, 0.0};
    for (uint32_t ac = 0; ac < 4; ++ac)
    {
        uint64_t totalBytes = 0;
        for (auto& sink : sinks[ac])
        {
            totalBytes += sink->GetTotalRx();
        }
        thrMbps[ac] = (totalBytes * 8.0) / (simTime * 1e6);
    }

    // Sortie CSV : scenario,x_val,run,VO,VI,BE,BK
    double xVal = (scenario == "fig8") ? offeredPerAcMbps : static_cast<double>(nStas);
    std::cout << scenario << "," << xVal << "," << run << "," << thrMbps[0] << "," << thrMbps[1]
              << "," << thrMbps[2] << "," << thrMbps[3] << std::endl;

    Simulator::Destroy();
    return 0;
}
