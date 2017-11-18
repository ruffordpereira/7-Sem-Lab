//#include "ns3/simulator-module.h"
//#include "ns3/node-module.h"
#include "ns3/core-module.h"
//#include "ns3/common-module.h"
#include "ns3/global-route-manager.h"
//#include "ns3/helper-module.h"
#include "ns3/bridge-module.h"
#include "ns3/network-module.h"
#include "ns3/csma-module.h"
#include "ns3/internet-module.h"
#include "ns3/point-to-point-module.h"
#include "ns3/flow-monitor-module.h"
#include "ns3/applications-module.h"

using namespace ns3;

NS_LOG_COMPONENT_DEFINE ("EthernetLANExample");

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
  csma_bridge_0.SetChannelAttribute ("Delay",  TimeValue (MilliSeconds (10)));

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
  uint16_t port_udpEcho_0 = 8;
  UdpEchoServerHelper server_udpEcho_0 (port_udpEcho_0);
  ApplicationContainer apps_udpEcho_0 = server_udpEcho_0.Install (term_5.Get(0));
  apps_udpEcho_0.Start (Seconds (1.0));
  apps_udpEcho_0.Stop (Seconds (10.0));
  Time interPacketInterval_udpEcho_0 = Seconds (1.0);
  UdpEchoClientHelper client_udpEcho_0 (iface_ndc_bridge_0.GetAddress(5), 8);
  client_udpEcho_0.SetAttribute ("MaxPackets", UintegerValue (10));
  client_udpEcho_0.SetAttribute ("Interval", TimeValue (interPacketInterval_udpEcho_0));
  client_udpEcho_0.SetAttribute ("PacketSize", UintegerValue (1024));
  apps_udpEcho_0 = client_udpEcho_0.Install (term_0.Get (0));
  apps_udpEcho_0.Start (Seconds (1.1));
  apps_udpEcho_0.Stop (Seconds (10.0));
  
  
  csma_bridge_0.EnablePcap ("second", ndc_bridge_0.Get (1), true);

  FlowMonitorHelper flowmon;
  Ptr<FlowMonitor> monitor = flowmon.InstallAll();

  NS_LOG_INFO("RUN SIMULATION");
  Simulator::Stop (Seconds(9.0));
  Simulator::Run ();
   
  monitor->CheckForLostPackets ();

  Ptr<Ipv4FlowClassifier> classifier = DynamicCast<Ipv4FlowClassifier> (flowmon.GetClassifier ());
  std::map<FlowId, FlowMonitor::FlowStats> stats = monitor->GetFlowStats ();
  for (std::map<FlowId, FlowMonitor::FlowStats>::const_iterator i = stats.begin (); i != stats.end (); ++i)
    {
	 Ipv4FlowClassifier::FiveTuple t = classifier->FindFlow (i->first);
      if ((t.sourceAddress=="10.0.0.1" && t.destinationAddress == "10.0.0.6"))
      {
            std::cout << "Flow " << i->first  << " (" << t.sourceAddress << " -> " << t.destinationAddress << ")\n";
            std::cout << "  Tx Bytes:   " << i->second.txBytes << "\n";
            std::cout << "  Rx Bytes:   " << i->second.rxBytes << "\n";
      	 std::cout << "  Throughput: " << i->second.rxBytes * 8.0 / (i->second.timeLastRxPacket.GetSeconds() - i->second.timeFirstTxPacket.GetSeconds())/1024/1024  << " Mbps\n";
        }
     }
 
   //monitor->SerializeToXmlFile("lab4.flowmon", true, true);
	
   Simulator::Destroy ();
   return 0;

  /* Simulation. */
  /* Pcap output. */
  /* Stop the simulation after x seconds. */
  //uint32_t stopTime = 11;
  //Simulator::Stop (Seconds (stopTime));
  /* Start and clean simulation. */
  //Simulator::Run ();
  //Simulator::Destroy ();
}