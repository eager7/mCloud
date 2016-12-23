#!/usr/bin/env python
# -*- coding: utf-8 -*-
__author__ = 'Chandler.Pan'
__metaclass__ = type

import zmq, time

PUB_ADDRESS = "tcp://127.0.0.1:5555"
PULL_ADDRESS = "tcp://127.0.0.1:5556"


class mZeroMqPullPush():
    '''
        这个类用作服务器接收客户端的请求，服务器是Pull类型，客户端是Push类型，因此可以实现多对一'''
    def __init__(self, address):
        super(mZeroMqPullPush, self).__init__()
        self.context = zmq.Context()
        self.receiver = self.context.socket(zmq.PULL)
        self.receiver.connect(address)

    def Receive(self):
        return self.receiver.recv_json()


class mZeroMqPubSub():
    '''
         这个类用作服务器向网关请求消息时使用，网关端用sub，因此可实现一对多'''
    def __init__(self, address):
        super(mZeroMqPubSub, self).__init__()
        try:
            self.context = zmq.Context()
            self.publisher = self.context.socket(zmq.PUB)
            self.publisher.bind(address)
        except Exception, e:
            print e

    def Publish(self, message):
        print 'send:', message
        self.publisher.send_json(message)

if __name__ == '__main__':
    print "test self"
    #mClass = mZeroMqPullPush(PULL_ADDRESS)
    #print mClass.Receive()

    mPub = mZeroMqPubSub(PUB_ADDRESS)
    time.sleep(1)
    mPub.Publish('{\"name\":\"BeJson\"}')
    mPub.Publish('{\"name\":\"BeJson\"}')
