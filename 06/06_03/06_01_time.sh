cd ~/cpp_course/06/06_01

rm -f *.o my_program

echo "------------------------------------------------"
echo "  06_01"
echo "------------------------------------------------"

echo "[1/3] Compiling Rational.cpp..."
time g++ -std=c++20 -c Rational.cpp -o Rational.o

echo ""
echo "[2/3] Compiling main.cpp..."
time g++ -std=c++20 -c main.cpp -o main.o

echo ""
echo "[3/3] Linking..."
time g++ Rational.o main.o -o my_program

echo ""
echo "File sizes:"
du -h Rational.o main.o my_program
