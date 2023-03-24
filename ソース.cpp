#include<iostream>
#include<vector>

using namespace std;

class koma {//駒の定義
public:
	/*koma() {
		cout << "komaコンスト" << endl;
	}
	virtual ~koma() {
		cout << "komaデスト" << endl;
	}*/
	//void look();
	string put_s(int n);
private:
	string p[19] = { "王","金","銀","桂","香","飛","角","歩","馬","竜"};
};

string koma::put_s(int n) {
	if (n == 0 or n==8) {
		return p[4];
	}
	else if (n == 1 or n == 7) {
		return p[3];
	}
	else if (n == 2 or n == 6) {
		return p[2];
	}
	else if (n == 3 or n == 5) {
		return p[1];
	}
	else if (n == 4){
		return p[0];
	}
	else if (n == 10) {
		return p[5];
	}
	else if (n == 16) {
		return p[6];
	}
	else if (n < 27) {
		if (n > 17) {
			return p[7];
		}
		else {
			return "　";
		}
	}
}

/*void koma::look() {
	cout << p;
};*/


class choose {
public:
	choose(int a);
	unsigned int select();
	virtual ~choose();
private:
	string  z;
};

choose::choose(int a)
{
	if (a == 1) {
		cout << endl << "移動したい駒を段、筋で選択" << endl;
	}
	else {
		cout << endl << "移動したい場所を段、筋で選択" << endl;
	}
};

choose::~choose() {
	cout <</*" chooseデストだよ"<<*/endl;
}

class ugoku :public koma {
public:
	ugoku(string s);
	virtual ~ugoku();
	int check_move(string s, int x,int y,int X,int Y);
private:
	int a;
};
int ugoku::check_move(string s, int x,int y,int X,int Y) {
	int i=1;
	int z = (10 * X + Y) - 10 - X;
	int xy = (10 * x + y) - 10 - x;
	if (s=="歩↓") {
		i=(x==X+1 and y==Y);
	}
	else if (s == "歩↑") {
		i=(x==X-1 and y==Y);
	}
	else if (s == "香↓" or s == "香↑") {
		i=(x==X);
	}
	else if (s=="桂↑") {
		i=(x==X-2 and (y==Y+1 or y==Y-1));
	}
	else if (s == "桂↓") {
		i = (x == X + 2 && (y == Y + 1 or y == Y - 1));
	}
	else if (s == "銀↓") {
		i = (((x == X + 1) and (y == Y or y == Y + 1 or y == Y - 1)) or (x == X - 1 and (y == Y + 1 or y==Y-1)));
	}
	else if(s=="銀↑"){
		i = ((x == X - 1 and (y == Y or y == Y + 1 or y == Y - 1)) or (x ==X + 1 and (y == Y + 1 or y == Y - 1)));
	}
	else if (s == "金↓") {
		i= ((x == X + 1 and (y == Y or y == Y+ 1 or y == Y - 1)) or y==Y+1 or y==Y-1 or x==X-1);
	}
	else if (s == "金↑") {
		i = ((x == X - 1 and (y == Y or y == Y + 1 or y == Y - 1)) or y == Y + 1 or y == Y - 1 or x == X + 1);
	}
	else if (s == "王↑" or s == "王↓") {
		i = (((x == X + 1) and (y == Y - 1 or y == Y + 1 or y == Y)) or ((x == X - 1) and (y == Y - 1 or y == Y + 1 or y == Y)));
	}
	else if (s == "飛↓" or s == "飛↑") {
		i = (x == X or y == Y);
	}
	else if (s=="角↑" or s=="角↓") {
		int a, b,c;
		for (a = 1; a < 10; a++) {
			b = 8;
			c = 10;
			i = (xy == xy + b or xy == xy - b or xy == xy -  c or xy == xy + c);
			b += b;
			c += c;
			if (i == 1) {
				break;
			}
		}
	}
	return i;
}
ugoku::ugoku(string s) {
	cout << s << "をどこに移動しますか？" << endl;
}
ugoku::~ugoku() {
	cout << endl << "手番が移ります";
}


unsigned int choose::select() {
	while (1) {
	cout << "半角整数値で入力" << endl;
	cin >> z;
	int xy = atoi(z.c_str());
		if (1 <= xy) {
			if (xy <= 9) {
				return xy;
			}
			else {
				cout << "1～9で入力してください" << endl;
			}
		}
		else {
			cout << "1～9で入力してください" << endl;
		}
	}
}

void show_s(string s) {
	cout<<endl << s << endl;//main関数cout短くしたい
}


int main()
{
	cout << "***入力後はEnterキーを押すこと***"<<endl<<endl;
	int n,x,y,xy,z,X,Y,ban = 100;
	string v, check ;
	string* kifu = new string[100];

	for (n = 0; n < ban; n++)//盤面の確保
	{
		kifu[n] = {"　　"};
	}
	
	koma ko1,ko2;//ko1先手ko2後手として分離
	
	for (n = 0; n < 81; n++)//駒の配置
	{
		int s = n%9;
		if (n < 27) {//先手の駒配置
			kifu[n] = ko1.put_s(n);
			if (!(kifu[n] == "　")) {
				kifu[n] += "↓";
			}
			else {
				kifu[n] += "　";
			}
			cout << kifu[n] <<"　";
		}
		else if(n > 26 and n<54) {//空の盤面
			kifu[n] += "　";
			cout <<kifu[n];
		}
		else if(n>53){//後手の駒配置
			int m = 80 - n;//先手と逆に入れる
			kifu[n]= ko2.put_s(m);
			if (!(kifu[n] == "　")) {
				kifu[n] += "↑";
			}
			else {
				kifu[n] += "　";
			}
			cout << kifu[n] <<"　";
		}
		if (s == 8) {//xyが段ごとに9こずつ配置されるように改行
			cout << endl;
		}

	}
	int endmain = 0;
	while (endmain==0) {
		choose cobj1(1);
		check = "no";
		while (check == "no") {//正しい入出力で進む

			v = "段は？";
			show_s(v);
			x = cobj1.select();
			v = "筋は？";
			show_s(v);
			y = cobj1.select();
			xy = (10 * x + y) - 10 - x;
			cout << "動かす駒は" << kifu[xy] << "でよろしいですか？";
			cout << endl << "yes,noで解答(駒がない,yes,no以外の入力はno)";//駒が存在しyesなら次へ
			cin >> check;
			if (!(kifu[xy] == "　　　") && check == "yes") {

			}
			else {
				check = "no";
			}
		}

		ugoku u1(kifu[xy]);
		check = "no";
		X = x; 
		Y = y;
		z = xy;
		while (check == "no") {//正しい入出力で進む
			choose cobj11(2);
			v = "段は？";
			show_s(v);
			x = cobj11.select();
			v = "筋は？";
			show_s(v);
			y = cobj11.select();
			xy = (10 * x + y) - 10 - x;
			cout << "動かす場所は" << x << "段" << y << "筋" << "でよろしいですか？";
			cout << endl << "yes,noで解答(移動できない,yes,no以外の入力はno)";//駒が移動でき、yesなら次へ
			cin >> check;
			if (u1.check_move(kifu[z], x,y,X,Y) && check == "yes") {
				if (kifu[xy] == "王↓" or kifu[xy] == "王↑") {
					endmain++;
				}
				kifu[xy] = kifu[z];//指定座標に駒をコピー
				kifu[z] = "　　";
				if (!(xy % 9 == 8)) {
					//kifu[xy]+="　";//違和感消すやつ
				}

			}
			else {
				check = "no";
			}
		}
		for (n = 0; n < 81; n++)//駒の配置
		{
			int s = n % 9;
			if (n < 27) {//先手の駒配置
				//kifu[n] = ko1.put_s(n);
				/*if (!(kifu[n] == "　")) {
					kifu[n] += "↓";
				}
				else {
				kifu[n] += "　";
				}*/
				cout << kifu[n] << "　";

			}
			else if (n > 26 and n < 54) {//空の盤面
				cout << kifu[n];
			}
			else if (n > 53) {//後手の駒配置
				int m = 80 - n;//先手と逆に入れる
				//kifu[n] = ko2.put_s(m);
				/*if (!(kifu[n] == "　")) {
					kifu[n] += "↑";
				}
				else {*/
				//kifu[n] += "　";
				//}
				cout << kifu[n] << "　";
			}
			if (s == 8) {//xyが段ごとに9こずつ配置されるように改行
				cout << endl;
			}
		}
	}

}