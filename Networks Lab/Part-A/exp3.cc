//#include "ns3/simulator-module.h"
//#include "ns3/node-module.h"
#include "ns3/core-module.h"
#include "ns3/global-route-manager.h"
#include "ns3/bridge-module.h"
#include "ns3/network-module.h"
#include "ns3/internet-module.h"
#include "ns3/csma-module.h"
#include "ns3/applications-module.h"
#include<iostream>
#include<fstream>
#include<string>
#include<cassert>

using namespace ns3;

NS_LOG_COMPONENT_DEFINE ("CsmaPingExample");

static void PingRtt (std::string context, Time rtt)
{
	std::cout << context << " " <<rtt <<std::endl;
}
static void RxDrop (Ptr<const Packet>p)
{
	NS_LOG_UNCOND ("RxDrop at "<< Simulator::Now ().GetSeconds ());
}

int main(int argc, char *argv[])
{
  CommandLine cmd;
  cmd.Parse (argc, argv);

  /* Configuration. */

  /* Build nodes. */
  NodeContainer term_0;
  term_0.Create (1);
  NodeContainer term_1;
  term_1.Create (1);
  NodeContainer term_2;
  term_2.Create (1);
  NodeContainer term_3;
  term_3.Create (1);
  NodeContainer term_4;
  term_4.Create (1);
  NodeContainer term_5;
  term_5.Create (1);
  NodeContainer bridge_0;
  bridge_0.Create (1);

  /* Build link. */
  CsmaHelper csma_bridge_0;
  csma_bridge_0.SetChannelAttribute ("DataRate", DataRateValue (100000000));
  csma_bridge_0.SetChannelAttribute ("Delay",  TimeValue (MilliSeconds (1)));

  /* Build link net device container. */
  NodeContainer all_bridge_0;
  all_bridge_0.Add (term_0);
  all_bridge_0.Add (term_1);
  all_bridge_0.Add (term_2);
  all_bridge_0.Add (term_3);
  all_bridge_0.Add (term_4);
  all_bridge_0.Add (term_5);
  NetDeviceContainer terminalDevices_bridge_0;
  NetDeviceContainer BridgeDevices_bridge_0;
  for (int i = 0; i < 6; i++)
  {
   NetDeviceContainer link = csma_bridge_0.Install(NodeContainer(all_bridge_0.Get(i), bridge_0));
   terminalDevices_bridge_0.Add (link.Get(0));
   BridgeDevices_bridge_0.Add (link.Get(1));
  }
  BridgeHelper bridge_bridge_0;
  bridge_bridge_0.Install (bridge_0.Get(0), BridgeDevices_bridge_0);
  NetDeviceContainer ndc_bridge_0 = terminalDevices_bridge_0;

  /* Install the IP stack. */
  InternetStackHelper internetStackH;
  internetStackH.Install (term_0);
  internetStackH.Install (term_1);
  internetStackH.Install (term_2);
  internetStackH.Install (term_3);
  internetStackH.Install (term_4);
  internetStackH.Install (term_5);

  /* IP assign. */
  Ipv4AddressHelper ipv4;
  ipv4.SetBase ("10.0.0.0", "255.255.255.0");
  Ipv4InterfaceContainer iface_ndc_bridge_0 = ipv4.Assign (ndc_bridge_0);

  /* Generate Route. */
  Ipv4GlobalRoutingHelper::PopulateRoutingTables ();

  /* Generate Application. */
  Ptr<RateErrorModel> em= CreateObject<RateErrorModel> ();
  em->SetAttribute ("ErrorRate", DoubleValue (0.0001));
  ndc_bridge_0.Get (0)->SetAttribute ("ReceiveErrorModel",PointerValue (em));
  
  InetSocketAddress dst_ping_0 = InetSocketAddress (iface_ndc_bridge_0.GetAddress(0));
  OnOffHelper onoff_ping_0 = OnOffHelper ("ns3::Ipv4RawSocketFactory", dst_ping_0);
  onoff_ping_0.SetAttribute ("OnTime", StringValue("ns3::ConstantRandomVariable[Constant=1]"));
  onoff_ping_0.SetAttribute ("OffTime",StringValue("ns3::ConstantRandomVariable[Constant=0]"));
  ApplicationContainer apps_ping_0 = onoff_ping_0.Install(term_1.Get(0));
  apps_ping_0.Start (Seconds (1.1));
  apps_ping_0.Stop (Seconds (10.1));
  PacketSinkHelper sink_ping_0 = PacketSinkHelper ("ns3::Ipv4RawSocketFactory", dst_ping_0);
  apps_ping_0 = sink_ping_0.Install (term_0.Get(0));
  apps_ping_0.Start (Seconds (1.0));
  apps_ping_0.Stop (Seconds (10.2));
  V4PingHelper ping_ping_0 = V4PingHelper(iface_ndc_bridge_0.GetAddress(0));
  apps_ping_0 = ping_ping_0.Install(term_1.Get(0));
  apps_ping_0.Start (Seconds (1.2));
  apps_ping_0.Stop (Seconds (10.0));
  InetSocketAddress dst_ping_1 = InetSocketAddress (iface_ndc_bridge_0.GetAddress(2));
  OnOffHelper onoff_ping_1 = OnOffHelper ("ns3::Ipv4RawSocketFactory", dst_ping_1);
  onoff_ping_1.SetAttribute ("OnTime",StringValue("ns3::ConstantRandomVariable[Constant=1]"));
  onoff_ping_1.SetAttribute ("OffTime",StringValue("ns3::ConstantRandomVariable[Constant=0]"));
  ApplicationContainer apps_ping_1 = onoff_ping_1.Install(term_1.Get(0));
  apps_ping_1.Start (Seconds (1.1));
  apps_ping_1.Stop (Seconds (10.1));
  PacketSinkHelper sink_ping_1 = PacketSinkHelper ("ns3::Ipv4RawSocketFactory", dst_ping_1);
  apps_ping_1 = sink_ping_1.Install (term_2.Get(0));
  apps_ping_1.Start (Seconds (1.0));
  apps_ping_1.Stop (Seconds (10.2));
  V4PingHelper ping_ping_1 = V4PingHelper(iface_ndc_bridge_0.GetAddress(2));
  apps_ping_1 = ping_ping_1.Install(term_1.Get(0));
  apps_ping_1.Start (Seconds (1.2));
  apps_ping_1.Stop (Seconds (10.0));
  InetSocketAddress dst_ping_2 = InetSocketAddress (iface_ndc_bridge_0.GetAddress(3));
  OnOffHelper onoff_ping_2 = OnOffHelper ("ns3::Ipv4RawSocketFactory", dst_ping_2);
  onoff_ping_2.SetAttribute ("OnTime",StringValue("ns3::ConstantRandomVariable[Constant=1]"));
  onoff_ping_2.SetAttribute ("OffTime",StringValue("ns3::ConstantRandomVariable[Constant=0]"));
  ApplicationContainer apps_ping_2 = onoff_ping_2.Install(term_1.Get(0));
  apps_ping_2.Start (Seconds (1.1));
  apps_ping_2.Stop (Seconds (10.1));
  PacketSinkHelper sink_ping_2 = PacketSinkHelper ("ns3::Ipv4RawSocketFactory", dst_ping_2);
  apps_ping_2 = sink_ping_2.Install (term_3.Get(0));
  apps_ping_2.Start (Seconds (1.0));
  apps_ping_2.Stop (Seconds (10.2));
  V4PingHelper ping_ping_2 = V4PingHelper(iface_ndc_bridge_0.GetAddress(3));
  apps_ping_2 = ping_ping_2.Install(term_1.Get(0));
  apps_ping_2.Start (Seconds (1.2));
  apps_ping_2.Stop (Seconds (10.0));
  InetSocketAddress dst_ping_3 = InetSocketAddress (iface_ndc_bridge_0.GetAddress(4));
  OnOffHelper onoff_ping_3 = OnOffHelper ("ns3::Ipv4RawSocketFactory", dst_ping_3);
  onoff_ping_3.SetAttribute ("OnTime",StringValue("ns3::ConstantRandomVariable[Constant=1]"));
  onoff_ping_3.SetAttribute ("OffTime",StringValue("ns3::ConstantRandomVariable[Constant=0]"));
  ApplicationContainer apps_ping_3 = onoff_ping_3.Install(term_1.Get(0));
  apps_ping_3.Start (Seconds (1.1));
  apps_ping_3.Stop (Seconds (10.1));
  PacketSinkHelper sink_ping_3 = PacketSinkHelper ("ns3::Ipv4RawSocketFactory", dst_ping_3);
  apps_ping_3 = sink_ping_3.Install (term_4.Get(0));
  apps_ping_3.Start (Seconds (1.0));
  apps_ping_3.Stop (Seconds (10.2));
  V4PingHelper ping_ping_3 = V4PingHelper(iface_ndc_bridge_0.GetAddress(4));
  apps_ping_3 = ping_ping_3.Install(term_1.Get(0));
  apps_ping_3.Start (Seconds (1.2));
  apps_ping_3.Stop (Seconds (10.0));
  InetSocketAddress dst_ping_4 = InetSocketAddress (iface_ndc_bridge_0.GetAddress(5));
  OnOffHelper onoff_ping_4 = OnOffHelper ("ns3::Ipv4RawSocketFactory", dst_ping_4);
  onoff_ping_4.SetAttribute ("OnTime",StringValue("ns3::ConstantRandomVariable[Constant=1]"));
  onoff_ping_4.SetAttribute ("OffTime",StringValue("ns3::ConstantRandomVariable[Constant=0]"));
  ApplicationContainer apps_ping_4 = onoff_ping_4.Install(term_1.Get(0));
  apps_ping_4.Start (Seconds (1.1));
  apps_ping_4.Stop (Seconds (10.1));
  PacketSinkHelper sink_ping_4 = PacketSinkHelper ("ns3::Ipv4RawSocketFactory", dst_ping_4);
  apps_ping_4 = sink_ping_4.Install (term_5.Get(0));
  apps_ping_4.Start (Seconds (1.0));
  apps_ping_4.Stop (Seconds (10.2));
  V4PingHelper ping_ping_4 = V4PingHelper(iface_ndc_bridge_0.GetAddress(5));
  apps_ping_4 = ping_ping_4.Install(term_1.Get(0));
  apps_ping_4.Start (Seconds (1.2));
  apps_ping_4.Stop (Seconds (10.0));

  ndc_bridge_0.Get (0)->TraceConnectWithoutContext ("PhyRxDrop", MakeCallback(&RxDrop));

  Config::Connect ("/NodeList/*/ApplicationList/*/$ns3::V4Ping/Rtt", MakeCallback(&PingRtt));
  Packet::EnablePrinting ();

  /* Simulation. */
  /* Pcap output. */
  /* Stop the simulation after x seconds. */
  uint32_t stopTime = 11;
  Simulator::Stop (Seconds (stopTime));
  /* Start and clean simulation. */
  Simulator::Run ();
  Simulator::Destroy ();
}