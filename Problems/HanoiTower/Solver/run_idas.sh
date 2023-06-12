echo "IDA"
echo ">>>>>>>>>> 12Easy"
./HanoiTower12Disk.ida ../Definitions/HanoiTower12DiskAbstraction1BottomDiskLess ../Definitions/HanoiTower12DiskAbstraction11TopDiskLess < ./Benchmark/hanoi_4p12d.d=005
echo ""
echo ">>>>>>>>>> 12Medium"
./HanoiTower12Disk.ida ../Definitions/HanoiTower12DiskAbstraction1BottomDiskLess ../Definitions/HanoiTower12DiskAbstraction11TopDiskLess < ./Benchmark/hanoi_4p12d.d=2000
echo ""

echo ">>>>>>>>>> 12Hard"
./HanoiTower12Disk.ida ../Definitions/HanoiTower12DiskAbstraction1BottomDiskLess ../Definitions/HanoiTower12DiskAbstraction11TopDiskLess < ./Benchmark/hanoi_4p12d.d=2000000
echo ""

echo ">>>>>>>>>> 14Easy"
./HanoiTower14Disk.ida ../Definitions/HanoiTower14DiskAbstraction3BottomDiskless ../Definitions/HanoiTower14DiskAbstraction11TopDiskless < ./Benchmark/hanoi_4p14d.d=005
echo ""

echo ">>>>>>>>>> 14Medium"
./HanoiTower14Disk.ida ../Definitions/HanoiTower14DiskAbstraction3BottomDiskless ../Definitions/HanoiTower14DiskAbstraction11TopDiskless < ./Benchmark/hanoi_4p14d.d=2000
echo ""

echo ">>>>>>>>>> 14Hard"
./HanoiTower14Disk.ida ../Definitions/HanoiTower14DiskAbstraction3BottomDiskless ../Definitions/HanoiTower14DiskAbstraction11TopDiskless < ./Benchmark/hanoi_4p14d.d=2000000
echo ""

echo ">>>>>>>>>> 18Easy"
time ./HanoiTower18Disk.ida ../Definitions/HanoiTower18DiskAbstraction7BottomDiskless ../Definitions/HanoiTower18DiskAbstraction11TopDiskLess < ./Benchmark/hanoi_4p18d.d=005
echo ""

echo ">>>>>>>>>> 18Medium"
time ./HanoiTower18Disk.ida ../Definitions/HanoiTower18DiskAbstraction7BottomDiskless ../Definitions/HanoiTower18DiskAbstraction11TopDiskLess < ./Benchmark/hanoi_4p18d.d=2000
echo ""

echo ">>>>>>>>>> 18Hard"
time ./HanoiTower18Disk.ida ../Definitions/HanoiTower18DiskAbstraction7BottomDiskless ../Definitions/HanoiTower18DiskAbstraction11TopDiskLess < ./Benchmark/hanoi_4p18d.d=2000000
echo ""
echo ""

echo "Astar"
echo ">>>>>>>>>> 12Easy"
./HanoiTower12Disk.a ../Definitions/HanoiTower12DiskAbstraction1BottomDiskLess ../Definitions/HanoiTower12DiskAbstraction11TopDiskLess < ./Benchmark/hanoi_4p12d.d=005
echo ""
echo ">>>>>>>>>> 12Medium"
./HanoiTower12Disk.a ../Definitions/HanoiTower12DiskAbstraction1BottomDiskLess ../Definitions/HanoiTower12DiskAbstraction11TopDiskLess < ./Benchmark/hanoi_4p12d.d=2000
echo ""

echo ">>>>>>>>>> 12Hard"
./HanoiTower12Disk.a ../Definitions/HanoiTower12DiskAbstraction1BottomDiskLess ../Definitions/HanoiTower12DiskAbstraction11TopDiskLess < ./Benchmark/hanoi_4p12d.d=2000000
echo ""

echo ">>>>>>>>>> 14Easy"
./HanoiTower14Disk.a ../Definitions/HanoiTower14DiskAbstraction3BottomDiskless ../Definitions/HanoiTower14DiskAbstraction11TopDiskless < ./Benchmark/hanoi_4p14d.d=005
echo ""

echo ">>>>>>>>>> 14Medium"
./HanoiTower14Disk.a ../Definitions/HanoiTower14DiskAbstraction3BottomDiskless ../Definitions/HanoiTower14DiskAbstraction11TopDiskless < ./Benchmark/hanoi_4p14d.d=2000
echo ""

echo ">>>>>>>>>> 14Hard"
./HanoiTower14Disk.a ../Definitions/HanoiTower14DiskAbstraction3BottomDiskless ../Definitions/HanoiTower14DiskAbstraction11TopDiskless < ./Benchmark/hanoi_4p14d.d=2000000
echo ""

echo ">>>>>>>>>> 18Easy"
./HanoiTower18Disk.a ../Definitions/HanoiTower18DiskAbstraction7BottomDiskless ../Definitions/HanoiTower18DiskAbstraction11TopDiskLess < ./Benchmark/hanoi_4p18d.d=005
echo ""

echo ">>>>>>>>>> 18Medium"
./HanoiTower18Disk.a ../Definitions/HanoiTower18DiskAbstraction7BottomDiskless ../Definitions/HanoiTower18DiskAbstraction11TopDiskLess < ./Benchmark/hanoi_4p18d.d=2000
echo ""

echo ">>>>>>>>>> 18Hard"
./HanoiTower18Disk.a ../Definitions/HanoiTower18DiskAbstraction7BottomDiskless ../Definitions/HanoiTower18DiskAbstraction11TopDiskLess < ./Benchmark/hanoi_4p18d.d=2000000
echo ""
