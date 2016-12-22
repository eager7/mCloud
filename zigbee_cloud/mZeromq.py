#!/usr/bin/env python
# -*- coding: utf-8 -*-
__author__ = 'Chandler.Pan'
__metaclass__ = type

import zmq

PULL_ADDRESS = "127.0.0.1:"
PULL_PORT = 5556


class mZeroMqPullPush():
    '''
    这个类用作服务器接收客户端的请求，服务器是Pull类型，客户端是Push类型
    '''
    def __init__(self):
        super(mZeroMqPullPush, self).__init__()
        self.context = zmq.Context()
        self.receiver = self.context.socket(zmq.PULL)
        self.receiver.connect("tcp://" + PULL_ADDRESS + str(PULL_PORT) )

    def Recv(self):
        return self.receiver.recv_json()


if __name__ == '__main__':
    print "test self"
    mClass = mZeroMqPullPush()
    print mClass.Recv()