v 20130925 2
C 40000 40000 0 0 0 title-B.sym
T 50100 40700 9 10 1 0 0 0 1
Load Cell
T 50500 40100 9 10 1 0 0 0 1
1
T 52000 40100 9 10 1 0 0 0 1
1
T 54000 40100 9 10 1 0 0 0 1
Robert Lee
T 54000 40300 9 10 1 0 0 0 1
1.0
C 46000 43300 1 0 0 connector4-1.sym
{
T 47800 44200 5 10 0 0 0 0 1
device=CONNECTOR_4
T 46000 44700 5 10 1 1 0 0 1
refdes=Load Cell
T 46600 44200 5 10 1 1 0 0 1
netname=Black, Excitation -
}
T 46600 43600 5 10 1 1 0 0 1
netname=Green, Output Signal +
T 46600 43900 5 10 1 1 0 0 1
netname=White, Output Signal -
T 46600 44500 5 10 1 1 0 0 1
netname=Red, Excitation +
C 53000 43000 1 0 1 connector5-1.sym
{
T 51200 44500 5 10 0 0 0 6 1
device=CONNECTOR_5
T 52900 44700 5 10 1 1 0 6 1
refdes=Load Cell Amplifier Inputs
T 52000 44500 5 10 1 1 0 0 1
netname=RED
}
T 52000 44200 5 10 1 1 0 0 1
netname=BLK
T 52000 43900 5 10 1 1 0 0 1
netname=WHT
T 52000 43600 5 10 1 1 0 0 1
netname=GRN
T 52000 43300 5 10 1 1 0 0 1
netname=YLW
C 53000 45700 1 0 1 connector4-1.sym
{
T 51200 46600 5 10 0 0 0 6 1
device=CONNECTOR_4
T 53000 47100 5 10 1 1 0 6 1
refdes=Load Cell Amplifier
T 52400 46900 5 10 1 1 0 6 1
netname=VCC
}
T 50800 46600 5 10 1 1 0 0 1
netname=DAT (Output Signal)
T 50500 46300 5 10 1 1 0 0 1
netname=CLK (Signal Readiness)
T 52000 46000 5 10 1 1 0 0 1
netname=GND
N 51300 45900 47700 45900 4
N 47700 44100 51300 44100 4
N 47700 43500 51300 43500 4
N 47700 43800 51300 43800 4
N 47700 44400 51300 44400 4
N 47700 46200 51300 46200 4
N 51300 46500 47700 46500 4
C 46000 45700 1 0 0 connector4-1.sym
{
T 47800 46600 5 10 0 0 0 0 1
device=CONNECTOR_4
T 46000 47100 5 10 1 1 0 0 1
refdes=Arduino Digital Pins
T 46600 46900 5 10 1 1 0 0 1
netname=Persistent Digital High Output (5V)
}
N 47700 46800 51300 46800 4
T 46600 46000 5 10 1 1 0 0 1
netname=Persistent Digital Low Output (0V)
T 46600 46600 5 10 1 1 0 0 1
netname=Digital Input
T 46600 46300 5 10 1 1 0 0 1
netname=Digital Input
