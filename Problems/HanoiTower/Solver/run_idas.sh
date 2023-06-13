echo "IDA"
echo ">>>>>>>>>> 12Easy"
time ./HanoiTower12Disk.ida ../Definitions/HanoiTower12DiskAbstraction1BottomDiskLess ../Definitions/HanoiTower12DiskAbstraction11TopDiskLess < ./Benchmark/hanoi_4p12d.d=005
echo ""
echo ">>>>>>>>>> 12Medium"
time ./HanoiTower12Disk.ida ../Definitions/HanoiTower12DiskAbstraction1BottomDiskLess ../Definitions/HanoiTower12DiskAbstraction11TopDiskLess < ./Benchmark/hanoi_4p12d.d=2000
echo ""

echo ">>>>>>>>>> 12Hard"
time ./HanoiTower12Disk.ida ../Definitions/HanoiTower12DiskAbstraction1BottomDiskLess ../Definitions/HanoiTower12DiskAbstraction11TopDiskLess < ./Benchmark/hanoi_4p12d.d=2000000
echo ""

echo ">>>>>>>>>> 14Easy"
time ./HanoiTower14Disk.ida ../Definitions/HanoiTower14DiskAbstraction3BottomDiskless ../Definitions/HanoiTower14DiskAbstraction11TopDiskless < ./Benchmark/hanoi_4p14d.d=005
echo ""

echo ">>>>>>>>>> 14Medium"
time ./HanoiTower14Disk.ida ../Definitions/HanoiTower14DiskAbstraction3BottomDiskless ../Definitions/HanoiTower14DiskAbstraction11TopDiskless < ./Benchmark/hanoi_4p14d.d=2000
echo ""

echo ">>>>>>>>>> 14Hard"
time ./HanoiTower14Disk.ida ../Definitions/HanoiTower14DiskAbstraction3BottomDiskless ../Definitions/HanoiTower14DiskAbstraction11TopDiskless < ./Benchmark/hanoi_4p14d.d=2000000
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
