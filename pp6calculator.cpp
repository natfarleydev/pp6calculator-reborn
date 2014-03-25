#include <iostream>
#include <string>
#include <regex>
// #include <cmath>
#include <complex>

// TODO put these in separate files when CMake is working
class ThreeVector
{
private:
  double x_,y_,z_;
public:
  ThreeVector()
    : x_(0), y_(0), z_(0) {}
  ThreeVector(double x, double y, double z)
    : x_(x), y_(y), z_(z) {}
  double getx() const { return x_; }
  double gety() const { return y_; }
  double getz() const { return z_; }
  double setx(double x) { x_ = x; return x_; }
  double sety(double y) { y_ = y; return y_; }
  double setz(double z) { z_ = z; return z_; }
  double modulus();
};

double dot(ThreeVector a, ThreeVector b)
{
  ///
  /// Define the dot (inner) product of a ThreeVector
  /// 
  return a.getx()*b.getx() + a.gety()*b.gety() + a.getz()*b.getz();
}

double ThreeVector::modulus()
{
  ///
  /// Define the modulus of a ThreeVector
  /// 
  return sqrt(dot(*this,*this));
}

std::ostream& operator<<(std::ostream& s, const ThreeVector& c)
{
  ///
  /// Print a ThreeVector in the form (x, y, z)
  /// 
  s << "(" << c.getx() << ", " << c.gety() << ", " << c.getz() << ")";
  return s;
}

double interceptXAxis(double m, double c)
{
  ///
  /// A function to calculate the intercept on the x-axis of a straight line
  /// 
  return c/m;
}

struct quadraticRoots
{
  std::complex<double> root1,root2; 
};

std::ostream& operator<<(std::ostream& s, const quadraticRoots& c)
{
  ///
  /// Be smart about what to print when it comes to roots of quadratic equations
  /// 
  if(c.root1 == c.root2 && c.root1.imag() != 0)
    s << c.root1 << " (repeated root)";
  else if(c.root1 == c.root2 && c.root1.imag() == 0)
    s << c.root1.real() << " (repeated root)";
  else if(c.root1.imag() == 0 || c.root2.imag() == 0)
    s << c.root1.real() << " and " << c.root2.real();
  else 				// all that's left is root1, root2 are complex
    s << c.root1 << " and " << c.root2;
  return s;
}

quadraticRoots quadraticSolver(double aReal, double bReal, double cReal)
{
  quadraticRoots roots = quadraticRoots();
  roots.root1 = std::complex<double>(0,0);
  roots.root2 = std::complex<double>(0,0);

  std::complex<double> a = aReal;
  std::complex<double> b = bReal;
  std::complex<double> c = cReal;

  if((b*b - 4.0*a*c) == std::complex<double>(0,0))
    {
      roots.root1 = (-b)/(2.0*a);
      roots.root2 = roots.root1;
    }
  else
    {
      roots.root1 = (-b+sqrt(b*b-4.0*a*c))/(2.0*a);
      roots.root2 = (-b-sqrt(b*b-4.0*a*c))/(2.0*a);
    }
  return roots;
}

void coutChosen(std::string x)
{
  ///
  /// Function to cout "You have chosen the [x] function"
  /// 
  std::cout << "You have chosen the " << x << " function!" << std::endl;
}

template<typename T>
void promptForValue(T *x)
{
  ///
  /// Function for prompting for a single value, without spaces
  ///

  // Ask for it
  std::cout << "> ";
  std::cin >> *x;
}

int main(int argc, char *argv[])
{
  // string to decide what to do
  // TODO make it 'human' so that the user could type (e.g.)
  // > Please can I find out the intercept of a straight line on the x-axis
  // and the program knows what to do (by matching 'intercept' and 'x-axis')
  std::string decision;
  
  std::cout << "Hello World" << std::endl;

  std::cout << "Welcome to PP6Calculator (reborn). "
	    << "Please specify which function you would like to perform: "
	    << std::endl
	    << "> ";
  
  std::getline(std::cin,decision);
  
  if(std::regex_match(decision, std::regex("(^i$)|(.*intercept.*)")))
    {
      // initialise variables for y=mx+c
      double m,c;
      
      coutChosen("intercept");
      std::cout << "Please specify a gradient (m): ";
      std::cin >> m;
      std::cout << "Please specify an intercept (c): " << std::endl;
      std::cin >> c;
      std::cout << "The x intercept for the line y = " << m << "x + " << c
		<< " is " << interceptXAxis(m,c) << "." << std::endl;
    }
  else if(std::regex_match(decision, std::regex("(^q$)|(.*quadratic.*)")))
    {
      // Initialise variables for (-b±√(b^2 - 4ac))/(2a)
      double a, b, c;

      coutChosen("quadratic solver");
      std::cout << "Choose the x^2 term (a): " << std::endl << "> ";
      std::cin >> a;
      std::cout << "Choose the x term (b): " << std::endl << "> ";
      std::cin >> b;
      std::cout << "Choose the constant term (c): " << std::endl << "> ";
      std::cin >> c;

      std::cout << "The roots for your chosen quadratic are  "
		<< quadraticSolver(a,b,c) << std::endl;
    }
  else if(std::regex_match(decision,std::regex("(.*m$)|(.*modulus.*)")))
    {
      if(std::regex_match(decision,std::regex("(^3m$)|(.*\b3.vector.*modulus.*)")))
	{
	  // Initialise variables for the ThreeVector
	  double x,y,z;
	  coutChosen("3-vector modulus");
	  std::cout << "Choose the x term: " << std::endl;
	  promptForValue(&x);
	  std::cout << x << std::endl;
	  std::cout << "Choose the y term: " << std::endl;
	  promptForValue(&y);
	  std::cout << "Choose the z term: " << std::endl;
	  promptForValue(&z);

	  
	  std::cout << "The modulus of the 3-vector " <<  ThreeVector(x,y,z)
		    << " is " << (ThreeVector(x,y,z)).modulus() << std::endl;
	}
      else if(std::regex_match(decision,std::regex("(^4m$)|(.*\b4.vector.*modulus.*)")))
	{
	  std::cout << "You want to do a 4-vector modulus calculation" << std::endl;
	}
      else
	{
	  std::cout << "You want to do a modulus, but I'm not sure which one" << std::endl;
	}
    }
  else
    {
      std::cout << "You chose " << decision << std::endl;
      std::cout << "Sorry, I'm not yet complete enough to give you what you want."
		<< std::endl;
    }
  return 0;
}
