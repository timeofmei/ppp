import std;

int f(int);

int f(int x)
{
    return x + 1;
}

int main()
{
    int i = 7;
    std::cout << f(i) << '\n';
}
