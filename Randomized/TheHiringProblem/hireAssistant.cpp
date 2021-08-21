#include <iostream>


struct Candidate 
{
    std::string name;
    int quality;
    Candidate(std::string nom, int score)
    {
        name = nom; quality = score;
    }
};

void hireCandidate(Candidate c)
{
    std::cout << "Hired " << c.name << "!\n";
};

void hiringProcedure(Candidate candidates[] ,size_t n)
{
    size_t best = 0;
    for (size_t i = 0; i < n; i++)
    {
        if (candidates[i].quality > best) // Interview candidate; i.e read variable.
        {
            best = candidates[i].quality;
            hireCandidate(candidates[i]);
        }
    }

};

int main()
{
    Candidate c1 = Candidate("Tim",3);
    Candidate c2 = Candidate("Bob", 2);
    Candidate c3 = Candidate("Will", 1);

    Candidate candidates[] = {c1,c2,c3};
    hiringProcedure(candidates,3);

}