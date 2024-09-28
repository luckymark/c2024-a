#include<iostream>
#include<fstream>
#include<vector>
using namespace std;
fstream file;
class PushBox {
	int width, height;
	vector<vector<int>> __map;
	class boxes {
	public:
		int x,y;
		boxes(int _x, int _y):x(_x),y(_y) {}
	};
	class destinations {
	public:
		int x,y;
		destinations(int _x, int _y):x(_x),y(_y) {}
		bool have_box_on(const vector<boxes>& box) const {
			for(boxes b : box) {
				if(b.x == x && b.y == y) {
					return true;
				}
			}
			return false;
		}
	};
	vector<boxes> box;
	vector<destinations> dest;
public:
	PushBox(int w, int h):width(w),height(h),__map(vector<vector<int>>(h,vector<int>(w,0))) {}
	PushBox(const fstream& file,int level) {

	}
	PushBox(const PushBox&)=delete;
	PushBox& operator=(const PushBox&)=delete;
	void display() const {
		for (int i = 0; i < height; i++) {
			for (int j = 0; j < width; j++) {
				cout << __map[i][j] << " ";
			}
			cout << "\n";
		}
	}
};
#undef main
int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	cout<<"Hello World!"<<endl;
	return 0;
}