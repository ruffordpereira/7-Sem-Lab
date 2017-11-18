#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/internet-module.h"
#include "ns3/point-to-point-module.h"
#include "ns3/applications-module.h"
#include "ns3/netanim-module.h"

using namespace ns3;

int main(int argc, char *argv[])
{
  CommandLine cmd;
  cmd.Parse (argc, argv);

  /* Configuration. */
  Config::SetDefault ("ns3::OnOffApplication::PacketSize", UintegerValue (1024));
  Config::SetDefault ("ns3::OnOffApplication::DataRate", StringValue ("5Mbps"));

  std::string animFile = "exp2.xml";

  /* Build nodes. */
  NodeContainer term_0;
  term_0.Create (1);
  NodeContainer term_1;
  term_1.Create (1);
  NodeContainer term_2;
  term_2.Create (1);
  NodeContainer term_3;
  term_3.Create (1);

  /* Build link. */
  PointToPointHelper p2p_p2p_0;
  p2p_p2p_0.SetDeviceAttribute ("DataRate", DataRateValue (5000000));
  p2p_p2p_0.SetChannelAttribute ("Delay", TimeValue (MilliSeconds (2)));
  PointToPointHelper p2p_p2p_1;
  p2p_p2p_1.SetDeviceAttribute ("DataRate", DataRateValue (5000000));
  p2p_p2p_1.SetChannelAttribute ("Delay", TimeValue (MilliSeconds (2)));
  PointToPointHelper p2p_p2p_2;
  p2p_p2p_2.SetDeviceAttribute ("DataRate", DataRateValue (5000000));
  p2p_p2p_2.SetChannelAttribute ("Delay", TimeValue (MilliSeconds (2)));

  /* Build link net device container. */
  NodeContainer all_p2p_0;
  all_p2p_0.Add (term_0);
  all_p2p_0.Add (term_2);
  NetDeviceContainer ndc_p2p_0 = p2p_p2p_0.Install (all_p2p_0);
  NodeContainer all_p2p_1;
  all_p2p_1.Add (term_2);
  all_p2p_1.Add (term_3);
  NetDeviceContainer ndc_p2p_1 = p2p_p2p_1.Install (all_p2p_1);
  NodeContainer all_p2p_2;
  all_p2p_2.Add (term_1);
  all_p2p_2.Add (term_2);
  NetDeviceContainer ndc_p2p_2 = p2p_p2p_2.Install (all_p2p_2);

  /* Install the IP stack. */
  InternetStackHelper internetStackH;
  internetStackH.Install (term_0);
  internetStackH.Install (term_1);
  internetStackH.Install (term_2);
  internetStackH.Install (term_3);

  /* IP assign. */
  Ipv4AddressHelper ipv4;
  ipv4.SetBase ("10.0.0.0", "255.255.255.0");
  Ipv4InterfaceContainer iface_ndc_p2p_0 = ipv4.Assign (ndc_p2p_0);
  ipv4.SetBase ("10.0.1.0", "255.255.255.0");
  Ipv4InterfaceContainer iface_ndc_p2p_1 = ipv4.Assign (ndc_p2p_1);
  ipv4.SetBase ("10.0.2.0", "255.255.255.0");
  Ipv4InterfaceContainer iface_ndc_p2p_2 = ipv4.Assign (ndc_p2p_2);

  /* Generate Route. */
  Ipv4GlobalRoutingHelper::PopulateRoutingTables ();

  /* Generate Application. */
  uint16_t port_udpEcho_0 = 9;
  UdpEchoServerHelper server_udpEcho_0 (port_udpEcho_0);
  ApplicationContainer apps_udpEcho_0 = server_udpEcho_0.Install (term_3.Get(0));
  apps_udpEcho_0.Start (Seconds (1.0));
  apps_udpEcho_0.Stop (Seconds (10.0));
  Time interPacketInterval_udpEcho_0 = Seconds (0.001);
  UdpEchoClientHelper client_udpEcho_0 (iface_ndc_p2p_1.GetAddress(1), 9);
  client_udpEcho_0.SetAttribute ("MaxPackets", UintegerValue (30));
  client_udpEcho_0.SetAttribute ("Interval", TimeValue (interPacketInterval_udpEcho_0));
  client_udpEcho_0.SetAttribute ("PacketSize", UintegerValue (1024));
  apps_udpEcho_0 = client_udpEcho_0.Install (term_0.Get (0));
  apps_udpEcho_0.Start (Seconds (1.1));
  apps_udpEcho_0.Stop (Seconds (10.0));
  uint16_t port_tcp_0 = 8;
  Address sinkLocalAddress_tcp_0 (InetSocketAddress (Ipv4Address::GetAny (), port_tcp_0));
  PacketSinkHelper sinkHelper_tcp_0 ("ns3::TcpSocketFactory", sinkLocalAddress_tcp_0);
  ApplicationContainer sinkApp_tcp_0 = sinkHelper_tcp_0.Install (term_3);
  sinkApp_tcp_0.Start (Seconds (1.0));
  sinkApp_tcp_0.Stop (Seconds (10.0));
  OnOffHelper clientHelper_tcp_0 ("ns3::TcpSocketFactory", Address ());
  clientHelper_tcp_0.SetAttribute ("OnTime", StringValue ("ns3::ConstantRandomVariable[Constant=1]"));
  clientHelper_tcp_0.SetAttribute ("OffTime", StringValue ("ns3::ConstantRandomVariable[Constant=0]"));
  ApplicationContainer clientApps_tcp_0;
  AddressValue remoteAddress_tcp_0 (InetSocketAddress (iface_ndc_p2p_1.GetAddress (1), port_tcp_0));
  clientHelper_tcp_0.SetAttribute ("Remote", remoteAddress_tcp_0);
  clientApps_tcp_0.Add (clientHelper_tcp_0.Install (term_1));
  clientApps_tcp_0.Start (Seconds (1.1));
  clientApps_tcp_0.Stop (Seconds (10.0));

  /* Simulation. */
  AnimationInterface anim (animFile);
Ptr<Node> n = term_0.Get (0);
anim.SetConstantPosition (n, 100, 100);
n = term_1.Get (0);
anim.SetConstantPosition (n, 100, 200);
n = term_2.Get (0);
anim.SetConstantPosition (n, 200, 150);
n = term_3.Get (0);
anim.SetConstantPosition (n, 300, 150);
  
  /* Pcap output. */
  /* Stop the simulation after x seconds. */
  uint32_t stopTime = 11;
  Simulator::Stop (Seconds (stopTime));
  /* Start and clean simulation. */
  Simulator::Run ();
  Simulator::Destroy ();
}