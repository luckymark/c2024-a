#include<iostream>
#include<unordered_map>
#include <stdexcept>
#include<stack>
using namespace std;
pair<int, int> innerbrackets(const string &str) {
    int left = -1;
    for(int i = 0; i < str.size(); ++i) {
        if(str[i] == '(') left = i;
        if(str[i] == ')') {
            if(left > -1) return { left, i };
            else throw runtime_error("Invalid test example.");
        }
    }
    if(left > -1) throw runtime_error("Invalid test example.");
    return { -1, -1 };
}

string tostr(int i) {
    if(i == 0) return "0";
    int j = i;
    string ret;
    while(j > 0) {
        ret += (char) (j % 10 + '0');
        j /= 10;
    }
    reverse(ret.begin(), ret.end());
    return ret;
}

int toint(const string &s) {
    int ret = 0;
    bool neg = false;
    for(char ch : s) {
        if(ch == '-') neg = true;
        else if(ch >= '0' && ch <= '9') ret = ret * 10 + (ch - '0');
        else throw runtime_error("Invalid character in number.");
    }
    return neg ? -ret : ret;
}

int Calculate(const string &str) {
    auto [left, right] = innerbrackets(str);
    if(left == -1 && right == -1) {
        int numpos = 0;
		if(str[0] == '-') numpos = 1;
        for(; numpos < str.size(); ++numpos) {
            if(str[numpos] > '9' || str[numpos] < '0') break;
        }
        if(numpos == str.size()) return toint(str);
        auto mudipos = min(str.find('*'), str.find('/'));
        if(mudipos == string::npos) {
            if(str[numpos] == '+') {
                int secondnumpos = numpos + 1;
                for(; secondnumpos < str.size(); ++secondnumpos) {
                    if(str[secondnumpos] > '9' || str[secondnumpos] < '0') break;
                }
                string newstr;
                try {
                    int leftOperand = toint(str.substr(0, numpos));
                    int rightOperand = toint(str.substr(numpos + 1, secondnumpos - numpos - 1));
                    newstr = tostr(leftOperand + rightOperand) + str.substr(secondnumpos, string::npos);
                }
                catch(const std::exception &e) {
                    throw runtime_error("Invalid number format.");
                }
                return Calculate(newstr);
            }
            else {
                int secondnumpos = numpos + 1;
                for(; secondnumpos < str.size(); ++secondnumpos) {
                    if(str[secondnumpos] > '9' || str[secondnumpos] < '0') break;
                }
                string newstr;
                try {
                    int leftOperand = toint(str.substr(0, numpos));
                    int rightOperand = toint(str.substr(numpos + 1, secondnumpos - numpos - 1));
                    newstr = tostr(leftOperand - rightOperand) + str.substr(secondnumpos, string::npos);
                }
                catch(const std::exception &e) {
                    throw runtime_error("Invalid number format.");
                }
                return Calculate(newstr);
            }
        }
        else {
            if(str[mudipos] == '*') {
                int i = mudipos - 1;
                for(; i > 0; --i) {
                    if(str[i] < '0' || str[i] > '9') break;
                }
                int j = mudipos + 1;
                for(; j < str.size(); ++j) {
                    if(str[j] < '0' || str[j] > '9') break;
                }
                string newstr = str.substr(0, i ? i + 1 : 0)
                    + tostr(
                        (toint(str.substr(i ? (i + 1) : i, mudipos - (i ? i + 1 : i)))) *
                        (toint(str.substr(mudipos + 1, j - mudipos - (j < str.size()))))
                    )
                    + str.substr(j, string::npos);
                return Calculate(newstr);
            }
            else {
                int i = mudipos - 1;
                for(; i > 0; --i) {
                    if(str[i] < '0' || str[i] > '9') break;
                }
                int j = mudipos + 1;
                for(; j < str.size(); ++j) {
                    if(str[j] < '0' || str[j] > '9') break;
                }
                string newstr = str.substr(0, i ? i + 1 : 0)
                    + tostr(
                        (toint(str.substr(i ? (i + 1) : i, mudipos - (i ? i + 1 : i)))) /
                        (toint(str.substr(mudipos + 1, j - mudipos - (j < str.size()))))
                    )
                    + str.substr(j, string::npos);
                return Calculate(newstr);
            }
        }
    }
    else {
        string newstr = (str.substr(0, left))
            + tostr(Calculate(str.substr(left + 1, right - left - 1)))
            + str.substr(right + 1, str.size() - right - 1);
        return Calculate(newstr);
    }
}
/*
* Copilot的优化版，我写不出来
* 递归：
string calculateOperation(const string &str, int opPos, char op) {
    int i = opPos - 1;
    for (; i >= 0; --i) {
        if (str[i] < '0' || str[i] > '9') break;
    }
    int j = opPos + 1;
    for (; j < str.size(); ++j) {
        if (str[j] < '0' || str[j] > '9') break;
    }
    int leftOperand = toint(str.substr(i + 1, opPos - i - 1));
    int rightOperand = toint(str.substr(opPos + 1, j - opPos - 1));
    int result = (op == '*') ? leftOperand * rightOperand : leftOperand / rightOperand;
    return str.substr(0, i + 1) + tostr(result) + str.substr(j);
}

int Calculate(const string &str) {
    auto [left, right] = innerbrackets(str);
    if (left == -1 && right == -1) {
        int numpos = (str[0] == '-') ? 1 : 0;
        for (; numpos < str.size(); ++numpos) {
            if (str[numpos] > '9' || str[numpos] < '0') break;
        }
        if (numpos == str.size()) return toint(str);

        auto mudipos = min(str.find('*'), str.find('/'));
        if (mudipos == string::npos) {
            int secondnumpos = numpos + 1;
            for (; secondnumpos < str.size(); ++secondnumpos) {
                if (str[secondnumpos] > '9' || str[secondnumpos] < '0') break;
            }
            int leftOperand = toint(str.substr(0, numpos));
            int rightOperand = toint(str.substr(numpos + 1, secondnumpos - numpos - 1));
            int result = (str[numpos] == '+') ? leftOperand + rightOperand : leftOperand - rightOperand;
            return Calculate(tostr(result) + str.substr(secondnumpos));
        } else {
            return Calculate(calculateOperation(str, mudipos, str[mudipos]));
        }
    } else {
        string newstr = str.substr(0, left) + tostr(Calculate(str.substr(left + 1, right - left - 1))) + str.substr(right + 1);
        return Calculate(newstr);
    }
}
* 栈：
string calculateOperation(const string &str, int opPos, char op) {
    int i = opPos - 1;
    for (; i >= 0; --i) {
        if (str[i] < '0' || str[i] > '9') break;
    }
    int j = opPos + 1;
    for (; j < str.size(); ++j) {
        if (str[j] < '0' || str[j] > '9') break;
    }
    int leftOperand = toint(str.substr(i + 1, opPos - i - 1));
    int rightOperand = toint(str.substr(opPos + 1, j - opPos - 1));
    int result = (op == '*') ? leftOperand * rightOperand : leftOperand / rightOperand;
    return str.substr(0, i + 1) + tostr(result) + str.substr(j);
}

int Calculate(const string &str) {
    stack<string> exprStack;
    exprStack.push(str);

    while (!exprStack.empty()) {
        string currentExpr = exprStack.top();
        exprStack.pop();

        auto [left, right] = innerbrackets(currentExpr);
        if (left == -1 && right == -1) {
            int numpos = (currentExpr[0] == '-') ? 1 : 0;
            for (; numpos < currentExpr.size(); ++numpos) {
                if (currentExpr[numpos] > '9' || currentExpr[numpos] < '0') break;
            }
            if (numpos == currentExpr.size()) return toint(currentExpr);

            auto mudipos = min(currentExpr.find('*'), currentExpr.find('/'));
            if (mudipos == string::npos) {
                int secondnumpos = numpos + 1;
                for (; secondnumpos < currentExpr.size(); ++secondnumpos) {
                    if (currentExpr[secondnumpos] > '9' || currentExpr[secondnumpos] < '0') break;
                }
                int leftOperand = toint(currentExpr.substr(0, numpos));
                int rightOperand = toint(currentExpr.substr(numpos + 1, secondnumpos - numpos - 1));
                int result = (currentExpr[numpos] == '+') ? leftOperand + rightOperand : leftOperand - rightOperand;
                exprStack.push(tostr(result) + currentExpr.substr(secondnumpos));
            } else {
                exprStack.push(calculateOperation(currentExpr, mudipos, currentExpr[mudipos]));
            }
        } else {
            string newstr = currentExpr.substr(0, left) + tostr(Calculate(currentExpr.substr(left + 1, right - left - 1))) + currentExpr.substr(right + 1);
            exprStack.push(newstr);
        }
    }

    return 0; // This line should never be reached
}
*/

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	try {
		string str;
        while(true) {
            cin >> str;
            cout << Calculate(str) << "\n";
        }
		return 0;
	}
	catch(runtime_error &re) {
		cout << re.what();
		return -1;
	}
}