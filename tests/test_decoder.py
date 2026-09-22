import unittest
SIGNALS={0x100:("VehicleSpeed",0,16,0.01,0.0),0x101:("EngineRPM",0,16,0.25,0.0),0x102:("CoolantTemp",0,8,1.0,-40.0)}
def decode(cid,payload):
 if cid not in SIGNALS:return None
 n,s,l,sc,o=SIGNALS[cid]; r=int.from_bytes(payload,"little"); return n,((r>>s)&((1<<l)-1))*sc+o
class DecoderTests(unittest.TestCase):
 def test_speed(self): self.assertAlmostEqual(decode(0x100,bytes([0x10,0x27]))[1],100.0)
 def test_rpm(self): self.assertAlmostEqual(decode(0x101,bytes([0x80,0x3E]))[1],4000.0)
 def test_temperature(self): self.assertAlmostEqual(decode(0x102,bytes([90]))[1],50.0)
 def test_unknown(self): self.assertIsNone(decode(0x555,b"\0"))
if __name__=="__main__": unittest.main()