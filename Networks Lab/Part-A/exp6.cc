#include "ns3/core-module.h"
#include "ns3/global-route-manager.h"
#include "ns3/wifi-module.h"
#include "ns3/mobility-module.h"
#include "ns3/bridge-module.h"
#include "ns3/point-to-point-module.h"
#include "ns3/network-module.h"
#include "ns3/applications-module.h"
#include "ns3/internet-module.h"
#include "ns3/netanim-module.h"

using namespace ns3;

NS_LOG_COMPONENT_DEFINE ("WifiScriptExample");

int main(int argc, char *argv[])
{
  CommandLine cmd;
  cmd.Parse (argc, argv);

  /* Configuration. */
  LogComponentEnable ("UdpEchoClientApplication", LOG_LEVEL_INFO);
  LogComponentEnable ("UdpEchoServerApplication", LOG_LEVEL_INFO);

  std::string animFile="wifiudp.xml";
  
  /* Build nodes. */
  NodeContainer station_0;
  station_0.Create (1);
  NodeContainer station_1;
  station_1.Create (1);
  NodeContainer ap_0;
  ap_0.Create (1);
  NodeContainer term_0;
  term_0.Create (1);
  NodeContainer term_1;
  term_1.Create (1);

  /* Build link. */
  YansWifiPhyHelper wifiPhy_ap_0 = YansWifiPhyHelper::Default ();
  YansWifiChannelHelper wifiChannel_ap_0 = YansWifiChannelHelper::Default ();
  wifiPhy_ap_0.SetChannel (wifiChannel_ap_0.Create ());
  PointToPointHelper p2p_p2p_0;
  p2p_p2p_0.SetDeviceAttribute ("DataRate", DataRateValue (100000000));
  p2p_p2p_0.SetChannelAttribute ("Delay", TimeValue (MilliSeconds (10)));
  PointToPointHelper p2p_p2p_1;
  p2p_p2p_1.SetDeviceAttribute ("DataRate", DataRateValue (100000000));
  p2p_p2p_1.SetChannelAttribute ("Delay", TimeValue (MilliSeconds (10)));

  /* Build link net device container. */
  NodeContainer all_ap_0;
  NetDeviceContainer ndc_ap_0;
  
  Ssid ssid_ap_0 = Ssid ("ns-3-ssid");
  
  WifiHelper wifi_ap_0 = WifiHelper::Default ();
  
  NqosWifiMacHelper wifiMac_ap_0 = NqosWifiMacHelper::Default ();
  
  wifi_ap_0.SetRemoteStationManager ("ns3::AarfWifiManager");
  /*wifiMac_ap_0.SetType ("ns3::NqapWifiMac", 
     "Ssid", SsidValue (ssid_ap_0), 
     "BeaconGeneration", BooleanValue (true),
     "BeaconInterval", TimeValue (Seconds (2.5)));*/
   
   wifiMac_ap_0.SetType ("ns3::StaWifiMac","Ssid", 
    SsidValue (ssid_ap_0),"ActiveProbing", 
    BooleanValue (false));   
     
  ndc_ap_0.Add (wifi_ap_0.Install (wifiPhy_ap_0, wifiMac_ap_0, station_0));
  ndc_ap_0.Add (wifi_ap_0.Install (wifiPhy_ap_0, wifiMac_ap_0, station_1));
  
  /*wifiMac_ap_0.SetType ("ns3::NqstaWifiMac",
     "Ssid", SsidValue (ssid_ap_0), 
     "ActiveProbing", BooleanValue (false));*/
     
  wifiMac_ap_0.SetType ("ns3::ApWifiMac","Ssid",SsidValue (ssid_ap_0));
     
  ndc_ap_0.Add (wifi_ap_0.Install (wifiPhy_ap_0, wifiMac_ap_0, ap_0 ));
  
  MobilityHelper mobility_ap_0;
  
  mobility_ap_0.SetPositionAllocator ("ns3::GridPositionAllocator",
                                 "MinX", DoubleValue (0.0),
                                 "MinY", DoubleValue (0.0),
                                 "DeltaX", DoubleValue (5.0),
                                 "DeltaY", DoubleValue (10.0),
                                 "GridWidth", UintegerValue (3),
                                 "LayoutType", StringValue ("RowFirst"));

  mobility_ap_0.SetMobilityModel ("ns3::RandomWalk2dMobilityModel",
                             "Bounds", 
                             RectangleValue (Rectangle (-50, 50, -50, 50)));
  mobility_ap_0.Install (station_0);
  mobility_ap_0.Install (station_1);
  
  mobility_ap_0.SetMobilityModel ("ns3::ConstantPositionMobilityModel");
  
  mobility_ap_0.Install (ap_0);
  mobility_ap_0.Install(all_ap_0);
  
  NodeContainer all_p2p_0;
  all_p2p_0.Add (term_0);
  all_p2p_0.Add (ap_0);
  NetDeviceContainer ndc_p2p_0 = p2p_p2p_0.Install (all_p2p_0);
  NodeContainer all_p2p_1;
  all_p2p_1.Add (term_0);
  all_p2p_1.Add (term_1);
  NetDeviceContainer ndc_p2p_1 = p2p_p2p_1.Install (all_p2p_1);

  /* Install the IP stack. */
  InternetStackHelper internetStackH;
  internetStackH.Install (station_0);
  internetStackH.Install (station_1);
  internetStackH.Install (ap_0);
  internetStackH.Install (term_0);
  internetStackH.Install (term_1);

  /* IP assign. */
  Ipv4AddressHelper ipv4;
  ipv4.SetBase ("10.0.0.0", "255.255.255.0");
  Ipv4InterfaceContainer iface_ndc_ap_0 = ipv4.Assign (ndc_ap_0);
  ipv4.SetBase ("10.0.1.0", "255.255.255.0");
  Ipv4InterfaceContainer iface_ndc_p2p_0 = ipv4.Assign (ndc_p2p_0);
  ipv4.SetBase ("10.0.2.0", "255.255.255.0");
  Ipv4InterfaceContainer iface_ndc_p2p_1 = ipv4.Assign (ndc_p2p_1);

  /* Generate Route. */
  Ipv4GlobalRoutingHelper::PopulateRoutingTables ();

  /* Generate Application. */
  uint16_t port_udpEcho_0 = 8;
  UdpEchoServerHelper server_udpEcho_0 (port_udpEcho_0);
  ApplicationContainer apps_udpEcho_0 = server_udpEcho_0.Install (term_1.Get(0));
  apps_udpEcho_0.Start (Seconds (1.0));
  apps_udpEcho_0.Stop (Seconds (10.0));
  Time interPacketInterval_udpEcho_0 = Seconds (1.0);
  UdpEchoClientHelper client_udpEcho_0 (iface_ndc_p2p_1.GetAddress(1), 8);
  client_udpEcho_0.SetAttribute ("MaxPackets", UintegerValue (1));
  client_udpEcho_0.SetAttribute ("Interval", TimeValue (interPacketInterval_udpEcho_0));
  client_udpEcho_0.SetAttribute ("PacketSize", UintegerValue (1024));
  apps_udpEcho_0 = client_udpEcho_0.Install (station_0.Get (0));
  apps_udpEcho_0.Start (Seconds (1.1));
  apps_udpEcho_0.Stop (Seconds (10.0));

  /* Simulation. */
  AnimationInterface anim(animFile);
  /* Pcap output. */
  /* Stop the simulation after x seconds. */
  uint32_t stopTime = 11;
  Simulator::Stop (Seconds (stopTime));
  /* Start and clean simulation. */
  Simulator::Run ();
  Simulator::Destroy ();
}