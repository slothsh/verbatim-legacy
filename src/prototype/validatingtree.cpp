#include "../../include/prototype/validatingtree.hpp"

int main()
{
    constexpr ValidatingElement<size_t, true> a { 1, 4, 3 };

    std::cout << "Documents: " << a.documents << '\n';

    std::cout << "\nend\n";
    return 0;
}
