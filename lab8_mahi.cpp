#include <bits/stdc++.h>
using namespace std;

bool ip_accept = true;
vector<string> subnetid, D_Address;

string convert_binary(string s)
{
    string ans = "";
    int n = stoi(s);
    if (n > 255 || n < 0)
    {
        ip_accept = false;
        return "0";
    }
    while (n > 0)
    {
        ans += to_string(n % 2);
        n = n / 2;
    }
    reverse(ans.begin(), ans.end());
    while (ans.size() != 8)
    {
        ans = '0' + ans;
    }

    return ans;
}

void error()
{
    cout << "ip address is not acceptable \n";
}

string range(string append, string s)
{
    string ans = append + ".";
    int x = 128, val = 0;
    for (int i = 0; i < s.size(); i++)
    {
        if (i % 8 == 0 && i > 0)
        {
            ans += to_string(val) + ".";
            x = 128;
            val = 0;
        }
        if (s[i] == '1')
        {
            val += x;
        }
        x = x / 2;
    }
    ans += to_string(val);
    return ans;
}

void print_ranges(vector<string> ip, int i, int flag, int x, bool flag1)
{
    string append = "";
    int bits = 0;
    if (flag == 3)
    {
        append = ip[0] + "." + ip[1] + "." + ip[2];
        bits = 8;
    }
    else if (flag == 2)
    {
        append = ip[0] + "." + ip[1];
        bits = 16;
    }
    else if (flag == 1)
    {
        append = ip[0];
        bits = 24;
    }
    int n = i;
    string ans = "", ans1 = "", ans2 = "";

    while (n > 0)
    {
        ans += to_string(n % 2);
        n = n / 2;
    }

    reverse(ans.begin(), ans.end());
    while (ans.size() < log2(x))
    {
        ans = '0' + ans;
    }
    ans1 = ans2 = ans;
    while (ans1.size() != bits)
    {
        ans1 += "0";
        ans2 += "1";
    }
    if (flag1)
    {
        string x;
        x = range(append, ans1);
        subnetid.push_back(x);
        cout << x << " \t\t ";
        x = range(append, ans2);
        D_Address.push_back(x);
        cout << x << "\n";
    }
    else
    {
        string x;
        x = range(append, ans1);
        subnetid.push_back(x);
        cout << x << "\n";
    }
}

void ranges_subnet(vector<string> ip, int n, int flag)
{
    int i = 0, x = 0, bits = log2(n);
    if (flag == 3)
    {
        ip[3] = "0";
        while (i != n)
        {
            ip[3] = to_string(x + stoi(ip[3]));
            if (i != 0)
                cout << "subnet " << i << " : " << ip[0] << "." << ip[1] << "." << ip[2] << "." << ip[3] << "------>" << ip[0] << "." << ip[1] << "." << ip[2] << "." << to_string(stoi(ip[3]) + x - 1) << "\n";
            else
            {
                cout << "subnet " << i << " : " << ip[0] << "." << ip[1] << "." << ip[2] << "." << ip[3] << "------>" << ip[0] << "." << ip[1] << "." << ip[2] << "." << to_string((256 / n) - 1) << "\n";
            }
            x = 256 / n;
            i++;
        }
    }
    else
    {
        while (i != n)
        {
            cout << "subnet" << i + 1 << " \t\t";
            print_ranges(ip, i, flag, n, true);

            i++;
        }
    }
}

int main()
{
    string s, p = "";
    string sub_mask = "";

    cout << "enter the ip address : ";
    cin >> s;
    vector<string> ip;
    for (int i = 0; i < s.size(); i++)
    {
        if (s[i] == '.')
        {
            ip.push_back(p);
            p = "";
        }
        else
        {
            if (s[i] - '0' >= 0 && s[i] - '0' <= 9)
            {
                p += s[i];
            }
            else
            {
                error();
                return 0;
            }
        }
    }
    ip.push_back(p);

    if (ip.size() > 4)
    {
        error();
        return 0;
    }
    string ans = "";
    int flag = -1, bits = 0;
    string append = "";
    int class_def = stoi(ip[0]);
    if (class_def >= 0 && class_def <= 127)
    {
        flag = 1;
        bits = 24;
        append += ip[0];
        sub_mask = "255.";
        if (!(ip[1] == ip[2] && ip[2] == ip[3] && ip[2] == "0"))
        {
            error();
            exit(0);
        }
        cout << "CLASS A\n";
    }
    else if (class_def <= 191)
    {
        flag = 2;
        bits = 16;
        append += ip[0] + ip[1];
        sub_mask = "255.255.";
        if (!(ip[2] == ip[3] && ip[2] == "0"))
        {
            error();
            exit(0);
        }
        cout << "CLASS B\n";
    }
    else if (class_def <= 225)
    {
        flag = 3;
        bits = 8;
        append += ip[0] + ip[1] + ip[2];
        if (!(ip[3] == "0"))
        {
            error();
            exit(0);
        }
        sub_mask = "255.255.255.";
        cout << "CLASS C\n";
    }
    else if (class_def <= 239)
    {
        flag = 4;
        cout << "CLASS D\n";
    }
    else if (class_def <= 255)
    {
        flag = 5;
        cout << "CLASS E\n";
    }
    if (flag >= 4)
    {
        exit(0);
    }

    cout << "total no of IP Address (per subnet) : " << (1 << bits) << "\n\n";
    cout << "total no of usable hosts (per subnet) : " << (1 << bits) - 2 << "\n\n";
    int n;
    cout << "enter the no sections need to divide : ";
    cin >> n;

    if (ceil(log2(n)) != floor(log2(n)))
    {
        cout << "not valid as it is not a power of 2 \n";
        return 0;
    }

    int x = 0, i = 0;
    ip[3] = "0";

    cout << "\n ranges of ip address : \n\n";
    ranges_subnet(ip, n, flag);

    cout << "\n\nsubnet ids : \n\n";
    for (int i = 0; i < subnetid.size(); i++)
    {
        cout << "subnet" << i + 1 << "  \t" << subnetid[i] << "\n";
    }

    bits = log2(n);
    int ct = 0, val = 0;
    while (bits--)
    {
        val += (1 << (7 - bits));
    }
    sub_mask += to_string(val);
    if (flag == 2)
    {
        sub_mask += ".0";
    }
    else
    {
        sub_mask += ".0.0";
    }
    // cout << "subnetmask : " << sub_mask << "\n";

    cout << "\ndirect and limited broadcast address : \n\n";
    for (int i = 0; i < subnetid.size(); i++)
    {
        cout << "Subnet " << i + 1 << " : \t" << D_Address[i] << "\t   "
             << "255.255.255.255\n";
    }

    cout << "\n\n";
    cout << "Routing table for the above networks : \n";
    cout << "\nsubnetNO\t\tsubnetId\t\t\tsub_mask\t\t\tInterface\n";
    for (int i = 0; i < subnetid.size(); i++)
    {
        cout << i + 1 << "\t\t\t" << subnetid[i] << "\t\t\t" << sub_mask << "\t\t\t"
             << "I" << i + 1 << "\n";
    }
}

// 1- 127
// 128 - 191
// 192-225
// 224-239
// 240 - 255