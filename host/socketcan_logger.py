#!/usr/bin/env python3
import argparse,csv,socket,struct,time
SIGNALS={0x100:("VehicleSpeed",0,16,0.01,0.0),0x101:("EngineRPM",0,16,0.25,0.0),0x102:("CoolantTemp",0,8,1.0,-40.0)}
def decode(can_id,payload):
 if can_id not in SIGNALS:return None
 name,start,length,scale,offset=SIGNALS[can_id]
 raw=int.from_bytes(payload,"little"); return name,((raw>>start)&((1<<length)-1))*scale+offset
def main():
 p=argparse.ArgumentParser(); p.add_argument("--interface",default="can0"); p.add_argument("--duration",type=float,default=10.0); p.add_argument("--output",default="vehicle_log.csv"); a=p.parse_args()
 s=socket.socket(socket.PF_CAN,socket.SOCK_RAW,socket.CAN_RAW); s.bind((a.interface,)); deadline=time.monotonic()+a.duration
 with open(a.output,"w",newline="") as f:
  w=csv.writer(f); w.writerow(["timestamp_ms","can_id","signal","value"])
  while time.monotonic()<deadline:
   frame=s.recv(16); can_id,dlc=struct.unpack("=IB3x",frame[:8]); d=decode(can_id,frame[8:8+dlc])
   if d: w.writerow([int(time.time()*1000),hex(can_id),d[0],f"{d[1]:.3f}"])
 s.close()
if __name__=="__main__": main()