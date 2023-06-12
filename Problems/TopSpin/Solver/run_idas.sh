#el .pdb debe estar en Definitions, en este caso 15puzzleAbstraction1.pdb
echo "IDA"
echo ">>>>>>>>>> 12Easy"
./TopSpin12Token.ida ../Definitions/TopSpin12EvenToken ../Definitions/TopSpin12OddToken < ./Benchmark/topspin_12_4_d_005
echo ""
echo ">>>>>>>>>> 12Medium"
./TopSpin12Token.ida ../Definitions/TopSpin12EvenToken ../Definitions/TopSpin12OddToken < ./Benchmark/topspin_12_4.d=2000
echo ""

echo ">>>>>>>>>> 12Hard"
./TopSpin12Token.ida ../Definitions/TopSpin12EvenToken ../Definitions/TopSpin12OddToken < ./Benchmark/topspin_12_4.d=2000000
echo ""

echo ">>>>>>>>>> 14Easy"
./TopSpin14Token.ida ../Definitions/TopSpin14EvenToken ../Definitions/TopSpin14OddToken < ./Benchmark/topspin_14_4.d=005
echo ""

echo ">>>>>>>>>> 14Medium"
./TopSpin14Token.ida ../Definitions/TopSpin14EvenToken ../Definitions/TopSpin14OddToken < ./Benchmark/topspin_14_4.d=2000
echo ""

echo ">>>>>>>>>> 14Hard"
./TopSpin14Token.ida ../Definitions/TopSpin14EvenToken ../Definitions/TopSpin14OddToken < ./Benchmark/topspin_14_4.d=2000000
echo ""

echo ">>>>>>>>>> 17Easy"
./TopSpin17Token.ida ../Definitions/TopSpin17EvenToken ../Definitions/TopSpin17OddToken < ./Benchmark/topspin_17_4.d=005
echo ""

echo ">>>>>>>>>> 17Medium"
./TopSpin17Token.ida ../Definitions/TopSpin17EvenToken ../Definitions/TopSpin17OddToken < ./Benchmark/topspin_17_4.d=2000
echo ""

echo ">>>>>>>>>> 17Hard"
./TopSpin17Token.ida ../Definitions/TopSpin17EvenToken ../Definitions/TopSpin17OddToken < ./Benchmark/topspin_17_4.d=2000000
echo ""
echo ""

echo "Astar"
echo ">>>>>>>>>> 12Easy"
./TopSpin12Token.a ../Definitions/TopSpin12EvenToken ../Definitions/TopSpin12OddToken < ./Benchmark/topspin_12_4_d_005
echo ""
echo ">>>>>>>>>> 12Medium"
./TopSpin12Token.a ../Definitions/TopSpin12EvenToken ../Definitions/TopSpin12OddToken < ./Benchmark/topspin_12_4.d=2000
echo ""

echo ">>>>>>>>>> 12Hard"
./TopSpin12Token.a ../Definitions/TopSpin12EvenToken ../Definitions/TopSpin12OddToken < ./Benchmark/topspin_12_4.d=2000000
echo ""

echo ">>>>>>>>>> 14Easy"
./TopSpin14Token.a ../Definitions/TopSpin14EvenToken ../Definitions/TopSpin14OddToken < ./Benchmark/topspin_14_4.d=005
echo ""

echo ">>>>>>>>>> 14Medium"
./TopSpin14Token.a ../Definitions/TopSpin14EvenToken ../Definitions/TopSpin14OddToken < ./Benchmark/topspin_14_4.d=2000
echo ""

echo ">>>>>>>>>> 14Hard"
./TopSpin14Token.a ../Definitions/TopSpin14EvenToken ../Definitions/TopSpin14OddToken < ./Benchmark/topspin_14_4.d=2000000
echo ""

echo ">>>>>>>>>> 17Easy"
./TopSpin17Token.a ../Definitions/TopSpin17EvenToken ../Definitions/TopSpin17OddToken < ./Benchmark/topspin_17_4.d=005
echo ""

echo ">>>>>>>>>> 17Medium"
./TopSpin17Token.a ../Definitions/TopSpin17EvenToken ../Definitions/TopSpin17OddToken < ./Benchmark/topspin_17_4.d=2000
echo ""

echo ">>>>>>>>>> 17Hard"
./TopSpin17Token.a ../Definitions/TopSpin17EvenToken ../Definitions/TopSpin17OddToken < ./Benchmark/topspin_17_4.d=2000000
echo ""