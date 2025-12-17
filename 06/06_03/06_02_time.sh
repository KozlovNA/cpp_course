cd ~/cpp_course/06/06_02

rm -f *.o my_program
rm -rf gcm.cache

echo "------------------------------------------------"
echo "  06_02"
echo "------------------------------------------------"

echo "[1/5] Compiling Mixin.cppm..."
time g++ -std=c++20 -fmodules-ts -x c++ -c Mixin.cppm -o Mixin.o

echo ""
echo "[2/5] Compiling Rational.cppm..."
time g++ -std=c++20 -fmodules-ts -x c++ -c Rational.cppm -o Rational_iface.o

echo ""
echo "[3/5] Compiling Rational.cpp..."
time g++ -std=c++20 -fmodules-ts -c Rational.cpp -o Rational_impl.o

echo ""
echo "[4/5] Compiling main.cpp..."
time g++ -std=c++20 -fmodules-ts -c main.cpp -o main.o

echo ""
echo "[5/5] Linking..."
time g++ Mixin.o Rational_iface.o Rational_impl.o main.o -o my_program_module

echo ""
echo "File sizes:"
du -h Rational_iface.o Rational_impl.o main.o my_program_module gcm.cache/rational.gcm
