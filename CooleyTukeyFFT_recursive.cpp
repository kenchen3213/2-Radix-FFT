#include <iostream> 
#include <math.h>
#define pi 3.1415926536
using namespace std;
class Complex{
	public:
		Complex(){
			r=0;
			i=0;
		}
		Complex(const double a, const double b){
			r=a;
			i=b;
		}
		static double real(const Complex a){
			return a.r;
		}
		static double imag(const Complex a){
			return a.i;
		}
		void set_value(const double a, const double b){
			r=a;
			i=b;
		}
		friend ostream& operator<< (ostream& os, Complex& a){
			if (a.i>=0) os<<a.r<<"+"<<a.i<<"i";
			else os<<a.r<<a.i<<"i";
	    }
		static Complex Add(const Complex a, const Complex b){
			Complex result;
			result.r=a.r+b.r;
			result.i=a.i+b.i;
			return result;
		}
		friend Complex operator+(const Complex a, const Complex b){
			return Complex::Add(a,b); 
		}
		static Complex Minus(const Complex a, const Complex b){
			Complex result;
			result.r=a.r-b.r;
			result.i=a.i-b.i;
			return result;
		}
        friend Complex operator-(const Complex a, const Complex b){
        	return Complex::Minus(a,b);
		}
		static Complex Multiply(const Complex a, const Complex b){
			Complex result;
			result.r=a.r*b.r-a.i*b.i;
			result.i=a.r*b.i+a.i*b.r;
			return result;
		}
		friend Complex operator*(const Complex a, const Complex b){
			return Complex::Multiply(a,b);
		}
		static Complex conj(const Complex a){
			Complex result;
			result.r=a.r;
			result.i=-a.i;
			return result; 
		}
		static double abs(const Complex a){
			return sqrt(a.r*a.r+a.i*a.i); 
		}
	private:
		double r;
		double i;
};
void fft_recursive(Complex *input, int n){
	if (n==1) return;
	else{
		Complex odd[n/2];
		Complex even[n/2];
		int i,k;
		for (i=0; i<n/2; i++){
			even[i]=input[i*2];
			odd[i]=input[i*2+1];
		}
		fft_recursive(even,n/2);
		fft_recursive(odd,n/2);
		for (k=0; k<n/2; k++){
			Complex t, W;
			W.set_value(cos(2*pi*k/n),-sin(2*pi*k/n));
			t=odd[k]*W;
			input[k]=even[k]+t;
			input[k+n/2]=even[k]-t;
		}
	}
}
void fft(Complex *input, Complex *output, int n){
	int i;
	for (i=0; i<n; i++){
		output[i]=input[i];
	}
	fft_recursive(output,n);
}
int main()
{
	const int N=8;
	int i;
	Complex a[N], b[N];
    for (i=0; i<N; i++){
    	a[i].set_value(i+1,0);
	}
	fft(a,b,N);
	for (i=0; i<N; i++){
    	cout<<b[i]<<endl;
	}
	return 0;
}
