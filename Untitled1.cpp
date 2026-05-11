#include<iostream>
using namespace std;

int s[100];
int top = -1;

void Push(int s[100], int x){
	if(top >= 99){
		cout << "ngan xep day";
	}else{
			top++;
			s[top] = x;
	}
}
int Pop(int s[100]){
	if( top == -1){
		cout << "ngan xep rong";
	} else{
		int x = s[top];
		top--;
		return x;
	}
	
}
int main() {
    int n;
    cout << "Nhap n: ";
    cin >> n;

    while (n != 0) {
        Push(s, n % 16);
        n /= 16;
    }

    cout << "Co so 16: ";

    while (top != -1) {
    	int x = Pop(s);
    	if (x==10){
    		cout << "A";
		}
		else if (x==11){
			cout << "B";
		}
		else if (x==12){
			cout << "C";
		}
		else if (x==13){
			cout << "D";
		}
		else if (x==14){
			cout << "E";
		}
		else if (x==15){
			cout << "F";
		}
		else{
			cout << x;
		}
			
    }
}