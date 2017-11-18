#include <fstream>
#include <iostream>
#include <string>
#include <cassert>
#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/internet-module.h"
#include "ns3/point-to-point-module.h"
#include "ns3/applications-module.h"
#include "ns3/csma-module.h"
#include "ns3/bridge-module.h"

using namespace ns3;

NS_LOG_COMPONENT_DEFINE ("FifthExample");

class MyApp : public Application 
{
public:

  MyApp ();
  virtual ~MyApp();

  void Setup (Ptr<Socket> socket, Address address, uint32_t packetSize, uint32_t nPackets, DataRate dataRate);

private:
  virtual void StartApplication (void);
  virtual void StopApplication (void);

  void ScheduleTx (void);
  void SendPacket (void);

  Ptr<Socket>     m_socket;
  Address         m_peer;
  uint32_t        m_packetSize;
  uint32_t        m_nPackets;
  DataRate        m_dataRate;
  EventId         m_sendEvent;
  bool            m_running;
  uint32_t        m_packetsSent;
};

MyApp::MyApp ()
  : m_socket (0), 
    m_peer (), 
    m_packetSize (0), 
    m_nPackets (0), 
    m_dataRate (0), 
    m_sendEvent (), 
    m_running (false), 
    m_packetsSent (0)
{
}

MyApp::~MyApp()
{
  m_socket = 0;
}

void
MyApp::Setup (Ptr<Socket> socket, Address address, uint32_t packetSize, uint32_t nPackets, DataRate dataRate)
{
  m_socket = socket;
  m_peer = address;
  m_packetSize = packetSize;
  m_nPackets = nPackets;
  m_dataRate = dataRate;
}

void
MyApp::StartApplication (void)
{
  m_running = true;
  m_packetsSent = 0;
  m_socket->Bind ();
  m_socket->Connect (m_peer);
  SendPacket ();
}

void 
MyApp::StopApplication (void)
{
  m_running = false;

  if (m_sendEvent.IsRunning ())
    {
      Simulator::Cancel (m_sendEvent);
    }

  if (m_socket)
    {
      m_socket->Close ();
    }
}

void 
MyApp::SendPacket (void)
{
  Ptr<Packet> packet = Create<Packet> (m_packetSize);
  m_socket->Send (packet);

  if (++m_packetsSent < m_nPackets)
    {
      ScheduleTx ();
    }
}

void 
MyApp::ScheduleTx (void)
{
  if (m_running)
    {
      Time tNext (Seconds (m_packetSize * 8 / static_cast<double> (m_dataRate.GetBitRate ())));
      m_sendEvent = Simulator::Schedule (tNext, &MyApp::SendPacket, this);
    }
}

static void
CwndChange (uint32_t oldCwnd, uint32_t newCwnd)
{
  NS_LOG_UNCOND (Simulator::Now ().GetSeconds () << "\t" << newCwnd);
}

static void
RxDrop (Ptr<const Packet> p)
{
  NS_LOG_UNCOND ("RxDrop at " << Simulator::Now ().GetSeconds ());
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
  csma_bridge_0.SetChannelAttribute ("DataRate", DataRateValue (10000000));
  csma_bridge_0.SetChannelAttribute ("Delay",  TimeValue (NanoSeconds (6560)));

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

  Ptr<RateErrorModel> em = CreateObject<RateErrorModel> ();
  em->SetAttribute ("ErrorRate", DoubleValue (0.00001));
  ndc_bridge_0.Get (5)->SetAttribute ("ReceiveErrorModel", PointerValue (em));

  /* IP assign. */
  Ipv4AddressHelper ipv4;
  ipv4.SetBase ("10.0.0.0", "255.255.255.0");
  Ipv4InterfaceContainer iface_ndc_bridge_0 = ipv4.Assign (ndc_bridge_0);

  /* Generate Route. */
  //Ipv4GlobalRoutingHelper::PopulateRoutingTables ();

  /* Generate Application. */
  uint16_t port_tcp_0 = 8;
  //Address sinkLocalAddress_tcp_0 (InetSocketAddress (Ipv4Address::GetAny (), port_tcp_0));
  Address sinkLocalAddress_tcp_0 (InetSocketAddress (iface_ndc_bridge_0.GetAddress (5), port_tcp_0));

  //PacketSinkHelper sinkHelper_tcp_0 ("ns3::TcpSocketFactory", sinkLocalAddress_tcp_0);
  PacketSinkHelper sinkHelper_tcp_0 ("ns3::TcpSocketFactory", InetSocketAddress (Ipv4Address::GetAny (), port_tcp_0));
  ApplicationContainer sinkApp_tcp_0 = sinkHelper_tcp_0.Install (term_5);
  sinkApp_tcp_0.Start (Seconds (0.0));
  sinkApp_tcp_0.Stop (Seconds (20.0));
  
  /*OnOffHelper clientHelper_tcp_0 ("ns3::TcpSocketFactory", Address ());
  clientHelper_tcp_0.SetAttribute ("OnTime", StringValue("ns3::ConstantRandomVariable[Constant=1]"));
  clientHelper_tcp_0.SetAttribute ("OffTime", StringValue("ns3::ConstantRandomVariable[Constant=0]"));
  ApplicationContainer clientApps_tcp_0;
  AddressValue remoteAddress_tcp_0 (InetSocketAddress (iface_ndc_bridge_0.GetAddress (5), port_tcp_0));
  clientHelper_tcp_0.SetAttribute ("Remote", remoteAddress_tcp_0);
  clientApps_tcp_0.Add (clientHelper_tcp_0.Install (term_1));
  clientApps_tcp_0.Start (Seconds (1.1));
  clientApps_tcp_0.Stop (Seconds (20.0));*/
  
  Ptr<Socket> ns3TcpSocket = Socket::CreateSocket (term_1.Get (0), TcpSocketFactory::GetTypeId ());
  ns3TcpSocket->TraceConnectWithoutContext ("CongestionWindow", MakeCallback (&CwndChange));

  Ptr<MyApp> app = CreateObject<MyApp> ();
  app->Setup (ns3TcpSocket, sinkLocalAddress_tcp_0, 1040, 1000, DataRate ("1Mbps"));
  term_1.Get (0)->AddApplication (app);
  app->SetStartTime (Seconds (1.));
  app->SetStopTime (Seconds (20.));

  ndc_bridge_0.Get (5)->TraceConnectWithoutContext ("PhyRxDrop", MakeCallback (&RxDrop));

  /* Simulation. */
  /* Pcap output. */
  /* Stop the simulation after x seconds. */
  //uint32_t stopTime = 21;
  //Simulator::Stop (Seconds (stopTime));
  /* Start and clean simulation. */
  Simulator::Run ();
  Simulator::Destroy ();
}