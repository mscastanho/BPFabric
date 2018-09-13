#!/usr/bin/env python
import struct

from core import eBPFCoreApplication, set_event_handler
from core.packets import *

import time
import matplotlib
import threading

class QueryThread(threading.Thread):
    def __init__(self, event, connection):
        threading.Thread.__init__(self)
        self.stopped = event
        self.connection = connection

    def run(self):
        while not self.stopped.wait(5):
            self.connection.send(TableListRequest(table_name='traffichist'))


class SFCTestApplication(eBPFCoreApplication):

    @set_event_handler(Header.HELLO)
    def hello(self, connection, pkt):
        with open('../examples/sfc_test.o', 'rb') as f:
            print("Installing the SFF eBPF ELF")
            connection.send(InstallRequest(elf=f.read(),index=SFF))

        with open('../examples/learningswitch.o','rb') as f:
            elf = f.read()
            for i in range(1..16):
                print("Sending install for SFF%d" % i)
                idx = "SF%d" % i
                connection.send(InstallRequest(elf=elf,index=idx))

        connection.send(TableEntryInsertRequest(table_name="inports", key=eth_src, value=struct.pack('I', in_port)))

    @set_event_handler(Header.TABLE_LIST_REPLY)
    def table_list_reply(self, connection, pkt):
        plt.cla()
        plt.clf()

        num_bins = len(pkt.items) / 8
        x = range(num_bins)
        x_labels = [ '{} - {}'.format(i*64, (i+1)*64-1) for i in x ]
        data = [ struct.unpack_from('Q', pkt.items, i * pkt.entry.value_size)[0] for i in range(num_bins) ]

        plt.bar(x, data, align='center')
        plt.xticks(x, x_labels, rotation=70)

        print data
        plt.draw()
        plt.pause(0.01)

if __name__ == '__main__':
    TrafficHistApplication().run()
