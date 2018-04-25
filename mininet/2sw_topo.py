#!/usr/bin/env python

from mininet.net import Mininet
from mininet.topo import Topo
from mininet.cli import CLI

from eBPFSwitch import eBPFSwitch, eBPFHost

from time import sleep

class SingleSwitchTopo(Topo):
	def __init__(self, **opts):
		# Initialize topology and default options
		Topo.__init__(self, **opts)

		s1 = self.addSwitch('s1', switch_path="../softswitch/softswitch")
		s2 = self.addSwitch('s2', switch_path="../softswitch/softswitch")

		h1 = self.addHost('h1',ip="10.0.0.1/24",mac='00:04:00:00:00:01')
		h2 = self.addHost('h2',ip="10.0.0.2/24",mac='00:04:00:00:00:02')
		
		self.addLink(s1, s2)
		self.addLink(h1, s1)
		self.addLink(h2, s2)

def main():
    topo = SingleSwitchTopo()
    net = Mininet(topo = topo, host = eBPFHost, switch = eBPFSwitch, controller = None)

    net.start()
    CLI(net)
    net.stop()

if __name__ == '__main__':
    main()
