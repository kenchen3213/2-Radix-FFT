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
unsigned int bit_reverse(unsigned int x, const int n){
	int i, t=0;
	for (i=0; i<log2(n); i++){
		t = t << 1; //往左邊位移一個位元 
		t = t | (x & 1); 
		x = x >> 1; //往右邊位移一個位元 
	}
	return t; 
}
void fft_iterative(Complex *input, int n){
	int s, k, j;
	for (s=1; s<=log2(n); s++){
		int m=pow(2,s);
		Complex Wm;
		Wm.set_value(cos(2*pi/m),-sin(2*pi/m));
		for (k=0; k<n; k+=m){
			Complex W;
			W.set_value(1,0);
			for (j=0; j<m/2; j++){
				Complex t, u;
				t=W*input[k+j+m/2];
				u=input[k+j];
				input[k+j]=u+t;
				input[k+j+m/2]=u-t;
				W=W*Wm;
			} 
		}
	}
}
void fft(Complex *input, Complex *output, int n){
	unsigned int i, rev;
	for (i=0; i<n; i++){
		rev=bit_reverse(i,n);
		output[i]=input[rev];
	}
	fft_iterative(output,n);
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
