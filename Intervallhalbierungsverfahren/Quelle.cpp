#include <iomanip>
#include <iostream> 
#include <cassert> 
#include <cmath> 
#include <boost/rational.hpp> 


template< typename Q, typename R >
Q make_rational(const R& x, R eps = 1.E-6)
{
	using std::floor;
	assert(x > R(0)); // nur für positive Zahlen 
	if (x >= R(1))
		return Q::int_type(floor(x)) + make_rational< Q >(x - floor(x), eps);
	const R invR = 1 / x;                           // Kehrwert 
	const Q::int_type inv = Q::int_type(invR);  // Ganzzahl des Kehrwerts 
	const R rest = invR - inv;                    // Rest bestimmen 
												  // --  Epsilon nachführen ... 
	const R n_eps = inv * eps;
	if (n_eps > R(1) || rest <= (n_eps * inv) / (1 - n_eps)
		|| rest >= (R(1) - n_eps * (inv + 1)) / (R(1) + eps *(inv + 1)))
	{
		return Q(1, (2 * rest > R(1) ? inv + 1 : inv));
	}
	return Q::int_type(1) / (inv + make_rational< Q >(rest, 2 * eps*invR));
}


int main()
{
	using namespace std;
	
	double u;
	double o;
	double w;
	int anzahl;

	locale::global(locale("German_germany"));

	std::cout << "Zahl, aus der Wurzel berechnet werden soll: ";
	std::cin >> w;
	
	std::cout << "Untere Annäherungszahl: ";
	std::cin >> u;
	
	std::cout << "Obere Annäherungszahl: ";
	std::cin >> o;

	std::cout << "Anzahl der durchzuführenden Schritte: ";
	std::cin >> anzahl;

	
	for (int i = 0; i < anzahl; i++)
	{
		/*std::cout << "Untere Annäherungszahl: " << std::setprecision(20) << u << std::endl;
		std::cout << "Obere Annäherungszahl: " << std::setprecision(20) << o << std::endl;*/
		
		double m = (u + o) / 2;
		//std::cout << "Mittelwert: " << std::setprecision(20) << m << std::endl;
		
		double sm = m * m;
		//std::cout << "Mittelwert zum Quadrat: " << std::setprecision(20) << sm << std::endl;

		double d = o - u;
		 
		if (d == 1)
		{
			//cout << "Differenz: " << d << endl;
			cout << setprecision(20) << u << " " << o << " " << m << " " << sm << " " << d << endl;
		}
		else
		{
			//cout << "Differenz: " << make_rational< boost::rational< int > >(d) << endl;
			cout << setprecision(20) << u << " " << o << " " << m << " " << sm << " " << make_rational< boost::rational< int > >(d) << endl;
		}


		std::cout << "" << std::endl;

		if (sm < w)
		{
			u = m;
		}
		else
		{
			o = m;
		}
	}


	system("PAUSE");
	return 0;
}