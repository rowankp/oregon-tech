#!/usr/bin/python3

import subprocess
import os
import sys
import time
import unittest
import tarfile

# Pick a unique port for this user
PORT = str(50000+int(os.getenv('SSH_TTY').split('/')[3]))

def run(cmd):
    """Run a command with given parameters return the return code, stdout and stderr"""
    result = subprocess.run(
        cmd,
        stdout=subprocess.PIPE,
        stderr=subprocess.PIPE)
    out = result.stdout.decode('utf-8')
    err = result.stderr.decode('utf-8')
    return result.returncode, out, err


    def runin(cmd, stdin):
        """Run a command with given parameters and given input return the return code"""
        result = subprocess.Popen(cmd,stdin=subprocess.PIPE)
        result.wait()
        return result.returncode


    def run_server():
        """Run the server"""
        pid = subprocess.Popen(["./server", "-p", PORT]).pid
        # Give the server time to start
        time.sleep(0.1)
        return pid


    def kill_server(pid):
        """kill the server"""
        subprocess.run(["kill", str(pid)])


class TestCases(unittest.TestCase):

    def setUp(self):
        """Run before every test"""
        print("setUp()", os.path.exists('./testdatas'))
        if not os.path.exists('./testdatas'):
            print('Creating server test data directory')
            os.mkdir('./testdatas')
        if not os.path.exists('./testdatac'):
            print('Creating client test data directory')
            os.mkdir('./testdatac')
        if os.path.exists('testdata.tar'):
            print('Extracting test data')
            tar = tarfile.open('testdata.tar')
            tar.extractall()
            tar.close()
        else:
            print('No testdata.tar file found!', file=sys.stderr)

    def tearDown(self):
        """Run after every test"""
        pass

    def test_nothing(self):
        pass

    def test_server_no_port(self):
        """Verify the server error when no port"""
        (code, out, err) = run(["./server"]);
        self.assertEqual(code, 1)

    def test_client_no_host(self):
        """Verify the client error when no port"""
        (code, out, err) = run(["./client", "-p","12345", "hello.txt"]);
        self.assertEqual(code, 1)

    def test_client_no_port(self):
        """Verify the client error when no port"""
        (code, out, err) = run(["./client", "-h","localhost", "hello.txt"]);
        self.assertEqual(code, 1)

    def test_first_server_test(self):
        """Verify the server outputs are as expected"""
        (code, out, err) = run(["./server", "-p", "12345"]);
        self.assertEqual(code, 0)
        self.assertEqual(out, 'PORT: 12345\n')
        self.assertEqual(err, '')

#    def test_first_client_test(self):
#        """Verify the client outputs are as expected"""
#        (code, out, err) = run(["./client", "-h","localhost", "-p","12345", "hello.txt"]);
#        self.assertEqual(code, 0)
#        self.assertEqual(out, 'HOST: localhost PORT: 12345 hello.txt\n')
#        self.assertEqual(err, '')

    def test_client_host_and_ip(self):
        """Verify the client error when host name and ip address are specified"""
        (code, out, err) = run(["./client", "-h", "localhost", "-i", "123.45.6789", "-p", "12345"]);
        self.assertEqual(code, 1)

#    def test_first_client_server(self):
        #pid = run_server()
        #code = run(["./client", "-p", PORT, "-h", "localhost"], "quit")
        #self.assertEqual(code, 0)
        #kill_server(pid)


if __name__ == '__main__':
    print("Port:",PORT)
    unittest.main()
