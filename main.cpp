#include <iostream>
#include <vector>
#include <string>
#include <random>
#include <thread>
#include <algorithm>
#include <list>
using namespace std;

// なんか色々定義
// --命令指定対象--
void initializeList(vector<string> &list);
int selectRandomElement(vector<string> &list);
int selectRandomElement2(vector<string> &list);
int AntlselectElement(vector<string> &list);
void addInputToList(vector<string> &list);
// --王様指定対象--
void initializeList_people(vector<string> &list);
int selectRandomElement_people(vector<string> &list);
int AntlselectElement_people(vector<string> &list);
void addInputToList_people(vector<string> &list);
void peopleinfo();

void ctrl();
void listctrl();
void randomctrl();
void resetmain();
void end();
void info();
void stainfo();
int chest();

int random_items();
// 多分ここまで

// リスト
// メインリスト
vector<string> items;
// 指定済みリスト
vector<string> enditems;
// 指定リスト
vector<string> selectlist;
// 未指定リスト
vector<string> items_copy;
// 総合指定可能リスト
vector<string> selectall;

// 補助リスト
// 王様指定リスト
vector<string> select_people;
// 王様指定済みリスト
vector<string> endPeople;
// 王様未指定リスト
vector<string> items_people;

// ========================================
// ----------細かいもの----------
// ========================================

// リストを初期化して要素を追加する関数
void initializeList(vector<string> &list)
{
    list.push_back("項目1");
    list.push_back("項目2");
    list.push_back("項目3");
    list.push_back("項目4");
    list.push_back("項目5");
    list.push_back("項目6");
    list.push_back("項目7");
    list.push_back("項目8");
    list.push_back("項目9");
    list.push_back("項目10");
}

// ランダムエンジンをグローバルで定義（1回のみ初期化）
random_device rd;
mt19937 mt(rd());

int peoplego = 1;

// ========================================
// -----------命令対象操作けいとー----------
// ========================================

// 王様重複が無効な場合、指定リストから取り除きルーレットをする関数まとめ
void addMissingElements()
{
    selectall.clear();
    for (const string &el : items_copy)
    {
        if (find(select_people.begin(), select_people.end(), el) == select_people.end())
        {
            selectall.push_back(el);
        }
    }
}

// リストからランダムな要素のインデックスを選択し、その要素を削除する関数
int selectRandomElement(vector<string> &list)
{
    uniform_int_distribution<int> dist(0, list.size() - 1);
    int index = dist(mt); // ランダムに選ばれた要素のインデックス

    // return index; // 関数の戻り値はもはや必要ないが、エラーチェックなどに使えます
    if (list.empty())
    {
        // リストが空の場合、エラーにならないように-1を返す
        return -1;
    }

    // 選ばれた要素をenditemsに追加
    enditems.push_back(list[index]);

    // selectにも
    selectlist.push_back(list[index]);
    // 選ばれた要素をリストから削除する
    list.erase(list.begin() + index);

    // 削除された要素のインデックスを戻り値として返す
    return index;
}

int selectRandomElement2(vector<string> &list)
{
    uniform_int_distribution<int> dist(0, list.size() - 1);
    int index = dist(mt); // ランダムに選ばれた要素のインデックス
    // return index; // 関数の戻り値はもはや必要ないが、エラーチェックなどに使えます
    if (list.empty())
    {
        // リストが空の場合、エラーにならないように-1を返す
        return -1;
    }

    // 選ばれた要素をenditemsに追加
    enditems.push_back(list[index]);
    // selectにも
    selectlist.push_back(list[index]);
    // 選ばれた要素をリストから削除する

    auto it = find(items_copy.begin(), items_copy.end(), list[index]);
    // items_copy.erase(list.begin() + index);

    if (it != items_copy.end())
    {
        cout << "選択-> " << *it << endl;
        items_copy.erase(it);
    }
    else
    {
        cout << "Not found" << endl;
    }
    // 削除された要素のインデックスを戻り値として返す
    return index;
}

int selectRandomElement3(vector<string> &list)
{
    // return index; // 関数の戻り値はもはや必要ないが、エラーチェックなどに使えます
    if (list.empty())
    {
        // リストが空の場合、エラーにならないように-1を返す
        return -1;
    }

    int index;
    cout << "要素のインデックスを入力してください（0からスタート。キャンセルの場合対象外を選択）: ";
    cin >> index;

    if (cin.fail() || index < 0 || index >= list.size())
    {
        cin.clear();                                         // エラーフラグのクリア
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // バッファのクリア
        cout << "無効なインデックスが入力されました。\n";
    }
    else
    {
        // 選ばれた要素をenditemsに追加
    enditems.push_back(list[index]);

    // selectにも
    selectlist.push_back(list[index]);
    // 選ばれた要素をリストから削除する
    list.erase(list.begin() + index);
    cout << "インデックス " << index << " を指定しました。\n";
    }

    // 削除された要素のインデックスを戻り値として返す
    return index;
}

//  上の逆ではないけど、まぁほぼ逆、指定します。
int AntlselectElement(vector<string> &list)
{
    int index;
    cout << "戻す要素のインデックスを入力してください（0からスタート。キャンセルの場合対象外を選択）: ";
    cin >> index;

    if (cin.fail() || index < 0 || index >= list.size())
    {
        cin.clear();                                         // エラーフラグのクリア
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // バッファのクリア
        cout << "無効なインデックスが入力されました。\n";
    }
    else
    {
        // 選ばれた要素をitems_copyへ戻す
        items_copy.push_back(list[index]);
        // 選ばれた要素をリストから削除する
        list.erase(list.begin() + index);
        cout << "インデックス " << index << " の要素を戻しました。\n";
    }
    return index;
}

// リストへ追加
void addInputToList(vector<string> &list)
{
    string input;
    cout << "リストに追加する文字列を入力してください: ";

    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, input);
    int index = list.size(); // 新しい要素に割り当てるインデックス
    list.push_back(input);
    // リストに追加した要素に番号を付けて表示
    cout << "番号 " << index << ": \"" << input << "\" をリストに追加しました。\n";
}

// リストから削除
void removeElementFromList(vector<string> &list)
{
    int index;
    cout << "削除する要素のインデックスを入力してください（0からスタート。キャンセルの場合対象外を選択）: ";
    cin >> index;

    if (cin.fail() || index < 0 || index >= list.size())
    {
        cin.clear();                                         // エラーフラグのクリア
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // バッファのクリア
        cout << "無効なインデックスが入力されました。\n";
    }
    else
    {
        list.erase(list.begin() + index);
        cout << "インデックス " << index << " の要素が削除されました。\n";
    }
}

// ========================================
// ----------王様指定けいとー----------
// ========================================

// リストからランダムな要素のインデックスを選択し、その要素を削除する関数
int selectRandomElement_people(vector<string> &list)
{
    uniform_int_distribution<int> dist(0, list.size() - 1);
    int index = dist(mt); // ランダムに選ばれた要素のインデックス

    // return index; // 関数の戻り値はもはや必要ないが、エラーチェックなどに使えます
    if (list.empty())
    {
        // リストが空の場合、エラーにならないように-1を返す
        return -1;
    }

    // 選ばれた要素をendPeopleに追加
    endPeople.push_back(list[index]);

    // selectにも
    select_people.push_back(list[index]);
    // 選ばれた要素をリストから削除する
    list.erase(list.begin() + index);

    // 削除された要素のインデックスを戻り値として返す
    return index;
}

//  上の逆ではないけど、まぁほぼ逆、指定します。
int AntlselectElement_people(vector<string> &list)
{
    int index;
    cout << "戻す要素のインデックスを入力してください（0からスタート。キャンセルの場合対象外を選択）: ";
    cin >> index;

    if (cin.fail() || index < 0 || index >= list.size())
    {
        cin.clear();                                         // エラーフラグのクリア
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // バッファのクリア
        cout << "無効なインデックスが入力されました。\n";
    }
    else
    {
        // 選ばれた要素をitems_peppleへ戻す
        items_people.push_back(list[index]);
        // 選ばれた要素をリストから削除する
        list.erase(list.begin() + index);
        cout << "インデックス " << index << " の要素を戻しました。\n";
    }
    return index;
}

// リストへ追加入らないと思いました。

// リストから削除もいらないと思います。

int peoplesiz(vector<string> &list)
{
    return list.size();
}

// 王様指定確認系
void peopleinfo()
{
    int select = 0;
    while (true)
    {
        system("cls");
        stainfo();
        int resetselect = 0;

        // 現在のリスト
        int num1 = 0;
        cout << "\n王様未指定:\n----------\n";
        for (const string &nowitem : items_people)
        {
            cout << num1 << "]" << nowitem << endl;
            num1++;
        }
        cout << "----------\n";

        int num2 = 0;
        cout << "\n王様指定済み:\n----------\n";
        for (const string &nowitem : endPeople)
        {
            cout << num2 << "]" << nowitem << endl;
            num2++;
        }
        cout << "----------\n";

        // 選択画面
        cout << "コマンド選択:\n"
             << "  1:戻る\n"
             << "  2:----------\n"
             << "  3:王様指定消去\n"
             << "  4:王様を命令の指定対象にするか否か\n";
        if (select == 5)
        {
            cout << "有効な数(1,3,4)を入力してください。\n";
        }
        select = 0;
        cout << "\n選択: ";
        cin >> select;

        if (cin.fail())
        {
            cin.clear();                                         // エラーフラグのクリア
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // バッファのクリア
            continue;
        }

        switch (select)
        {
        case 1:
            return; // Whileループを抜ける
        case 2:
            select = 5;
            break;
        case 3:
            AntlselectElement_people(endPeople);
            cout << "続行するにはエンターキーを押してください・・・";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin.get();
            break;
        case 4:
            resetselect = 0;
            cout << "\n王様もルーレットに当てるか否かの設定を変えますか？(0でキャンセル、1で実行)\n"
                 << "現在の設定:";
            if (peoplego == 1)
            {
                cout << "当てない\n";
            }
            else if (peoplego == 0)
            {
                cout << "当てる\n";
            }
            cout << "選択:";
            cin >> resetselect;
            if (resetselect == 0)
            {
                break;
            }
            else if (resetselect == 1)
            {
                if (peoplego == 0)
                {
                    peoplego = 1;
                    cout << "王様を当てない設定にしました。\n";
                    cout << "続行するにはエンターキーを押してください・・・";
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cin.get();
                }
                else if (peoplego == 1)
                {
                    peoplego = 0;
                    cout << "王様を当てる設定にしました。\n";
                    cout << "続行するにはエンターキーを押してください・・・";
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cin.get();
                }
            }
            else
            {
                cout << "有効でない値が入力されたためキャンセルされました。\n";
                cout << "続行するにはエンターキーを押してください・・・";
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cin.get();
            }
            break;
        default:
            select = 5;
            break;
        }
    }
}

// ========================================

// ========================================
// ----------コントロール----------
// ========================================

void ctrl()
{
    int select = 0;
    while (true)
    {
        system("cls");
        stainfo();

        // 現在のリスト
        chest();

        // 選択画面
        cout << "コマンド選択:\n"
             << "  1:リスト操作\n"
             << "  2:ルーレット操作\n"
             << "  3:ルーレットリスト反映\n"
             << "  4:テスト用キャラ追加\n"
             << "  5:終了\n";
        if (select == 6)
        {
            cout << "有効な数(1～5)を入力してください。\n";
        }
        select = 0;
        cout << "\n選択: ";
        cin >> select;

        if (cin.fail())
        {
            cin.clear();                                         // エラーフラグのクリア
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // バッファのクリア
            continue;
        }

        switch (select)
        {
        case 1:
            listctrl();
            break;
        case 2:
            randomctrl();
            break;
        case 3:
            items_copy = items;   // コピーコンストラクタ
            items_people = items; // コピーコンストラクタ
            break;
        case 4:
            info();
            break;
        case 5:
            end();
            return; // Whileループを抜ける
        default:
            select = 6;
            break;
        }
    }
}

// １リストそーさ
void listctrl()
{
    int select = 0;
    while (true)
    {
        system("cls");
        stainfo();

        // 現在のリスト
        chest();

        // 選択画面
        cout << "<リスト操作画面>\n";
        cout << "コマンド選択:\n"
             << "  1:追加\n"
             << "  2:削除\n"
             << "  3:戻る\n";
        if (select == 6)
        {
            cout << "有効な数(1～3)を入力してください。\n";
        }
        select = 0;
        cout << "\n選択: ";
        cin >> select;

        if (cin.fail())
        {
            cin.clear();                                         // エラーフラグのクリア
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // バッファのクリア
            continue;
        }

        switch (select)
        {
        case 1:
            // ユーザーの入力をリストに追加
            addInputToList(items);
            break;
        case 2:
            // ユーザーの入力をリストから削除
            removeElementFromList(items);
            break;
        case 3:
            return; // Whileループを抜ける
        default:
            select = 6;
            break;
        }
    }

    ctrl();
}

// ２ルーレットそーさ
void randomctrl()
{
    int select = 0;
    int resetselect = 0;
    int itemsnum = 0;
    int num3 = 0;
    int numse = 0;
    random_device rd;
    mt19937 mt(rd());
    while (true)
    {
        system("cls");

        stainfo();
        // 現在のリスト
        int num1 = 0;
        cout << "\n未対象選択:\n----------\n";
        for (const string &nowitem : items_copy)
        {
            cout << num1 << "]" << nowitem << endl;
            num1++;
        }
        cout << "----------\n";

        // 選択済みリスト
        int num2 = 0;

        cout << "\n対象選択済み:\n----------\n";
        for (const string &nowitem : enditems)
        {
            cout << num2 << "]" << nowitem << endl;
            num2++;
        }

        cout << "----------\n";

        // 選択画面
        cout << "<ルーレット操作画面>\n";
        cout << "コマンド選択:\n"
             << "  1:1人選択"
             << "  2:2人選択"
             << "  3:3人選択\n"
             << "  4:X人選択"
             << "  5:指定消去\n"
             << "  41:名指し指定\n"
             << "--------------------\n"
             << "  6:王様指定"
             << "  7:王様指定確認・削除\n"
             << "====================\n"
             << "  8:指定消去&リスト反映\n"
             << "  9:王様指定削除&リスト読み込み\n"
             << "  0:戻る\n\n";
        if (select == 99)
        {
            cout << "有効な数(1～9,0)を入力してください。\n";
        }
        select = 0;

        // 王様表示
        cout << "==現在の王様:";
        for (const string &nowitem : select_people)
        {
            cout << nowitem << ":==";
        };
        cout << " 未指定数:" << peoplesiz(items_people) << "==\n";

        if (peoplego == 1)
        {
            cout << "王様を当てない設定です。\n";
        }
        else if (peoplego == 0)
        {
            cout << "===警告===王様が当たる設定です===\n";
        }

        cout << "\n選択: ";
        cin >> select;

        if (cin.fail())
        {
            cin.clear();                                         // エラーフラグのクリア
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // バッファのクリア
            continue;
        }

        if (peoplego == 1)
        {
            addMissingElements();

            itemsnum = selectall.size();
            uniform_int_distribution<int> dist(0, itemsnum);
            int random_number = dist(mt);

            // イテレータをリストの先頭に設定
            auto itr = selectall.begin();
        }
        else if (peoplego == 0)
        {
            itemsnum = items_copy.size();
            uniform_int_distribution<int> dist(0, itemsnum);
            int random_number = dist(mt);

            // イテレータをリストの先頭に設定
            auto itr = items_copy.begin();
        }
        else
        {
            cout << "予期せぬエラー\n";
        }

        switch (select)
        {
        case 1: // 1:1人選択
            if (peoplego == 1)
            {
                if (selectall.empty())
                {
                    selectlist.push_back("-----");
                    cout << "リストが空です。\n";
                    cout << "続行するにはエンターキーを押してください・・・";
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cin.get();
                }
                else
                {

                    int selectedItemIndex = selectRandomElement2(selectall); // ここでランダムに選んで削除

                    num3 = 0;
                    cout << "\n対象:\n----------\n";
                    for (const string &nowitem : selectlist)
                    {
                        cout << num3 << "]" << nowitem << endl;
                        num3++;
                    }
                    cout << "----------\n";
                    cout << "続行するにはエンターキーを押してください・・・";
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cin.get();
                    selectlist.clear();
                }
            }
            else if (peoplego == 0)
            {
                if (items_copy.empty())
                {
                    selectlist.push_back("-----");
                    cout << "リストが空です。\n";
                    cout << "続行するにはエンターキーを押してください・・・";
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cin.get();
                }
                else
                {

                    int selectedItemIndex = selectRandomElement(items_copy); // ここでランダムに選んで削除

                    num3 = 0;
                    cout << "\n対象:\n----------\n";
                    for (const string &nowitem : selectlist)
                    {
                        cout << num3 << "]" << nowitem << endl;
                        num3++;
                    }
                    cout << "----------\n";
                    cout << "続行するにはエンターキーを押してください・・・";
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cin.get();
                    selectlist.clear();
                }
            }
            break;
        case 2: // 2:2人選択
            if (peoplego == 0)
            {
                for (int i = 0; i < 2; ++i)
                {
                    if (items_copy.empty())
                    {
                        selectlist.push_back("-----");
                        cout << "リストが空です。\n";
                    }
                    else
                    {

                        int selectedItemIndex = selectRandomElement(items_copy); // ここでランダムに選んで削除
                    }
                }
                num3 = 0;
                cout << "\n対象:\n----------\n";
                for (const string &nowitem : selectlist)
                {
                    cout << num3 << "]" << nowitem << endl;
                    num3++;
                }
                cout << "----------\n";
                cout << "続行するにはエンターキーを押してください・・・";
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cin.get();
                selectlist.clear();
            }
            else if (peoplego == 1)
            {
                for (int i = 0; i < 2; ++i)
                {
                    addMissingElements();
                    if (selectall.empty())
                    {
                        selectlist.push_back("-----");
                        cout << "リストが空です。\n";
                    }
                    else
                    {

                        int selectedItemIndex = selectRandomElement2(selectall); // ここでランダムに選んで削除
                    }
                }
                num3 = 0;
                cout << "\n対象:\n----------\n";
                for (const string &nowitem : selectlist)
                {
                    cout << num3 << "]" << nowitem << endl;
                    num3++;
                }
                cout << "----------\n";
                cout << "続行するにはエンターキーを押してください・・・";
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cin.get();
                selectlist.clear();
            }
            break;
        case 3: // 3:3人選択
            if (peoplego == 0)
            {
                for (int i = 0; i < 3; ++i)
                {
                    if (items_copy.empty())
                    {
                        selectlist.push_back("-----");
                        cout << "リストが空です。\n";
                    }
                    else
                    {

                        int selectedItemIndex = selectRandomElement(items_copy); // ここでランダムに選んで削除
                    }
                }
                num3 = 0;
                cout << "\n対象:\n----------\n";
                for (const string &nowitem : selectlist)
                {
                    cout << num3 << "]" << nowitem << endl;
                    num3++;
                }
                cout << "----------\n";
                cout << "続行するにはエンターキーを押してください・・・";
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cin.get();
                selectlist.clear();
            }
            else if (peoplego == 1)
            {
                for (int i = 0; i < 3; ++i)
                {
                    addMissingElements();
                    if (selectall.empty())
                    {
                        selectlist.push_back("-----");
                        cout << "リストが空です。\n";
                    }
                    else
                    {

                        int selectedItemIndex = selectRandomElement2(selectall); // ここでランダムに選んで削除
                    }
                }
                num3 = 0;
                cout << "\n対象:\n----------\n";
                for (const string &nowitem : selectlist)
                {
                    cout << num3 << "]" << nowitem << endl;
                    num3++;
                }
                cout << "----------\n";
                cout << "続行するにはエンターキーを押してください・・・";
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cin.get();
                selectlist.clear();
            }
            break;
        case 4: // 4:X人選択
            cout << "選択人数を指定してください:";
            cin >> numse;
            if (peoplego == 0)
            {
                for (int i = 0; i < numse; ++i)
                {
                    if (items_copy.empty())
                    {
                        selectlist.push_back("-----");
                        cout << "リストが空です。\n";
                    }
                    else
                    {

                        int selectedItemIndex = selectRandomElement(items_copy); // ここでランダムに選んで削除
                    }
                }
                num3 = 0;
                cout << "\n対象:\n----------\n";
                for (const string &nowitem : selectlist)
                {
                    cout << num3 << "]" << nowitem << endl;
                    num3++;
                }
                cout << "----------\n";
                cout << "続行するにはエンターキーを押してください・・・";
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cin.get();
                selectlist.clear();
            }
            else if (peoplego == 1)
            {
                for (int i = 0; i < numse; ++i)
                {
                    addMissingElements();
                    if (selectall.empty())
                    {
                        selectlist.push_back("-----");
                        cout << "リストが空です。\n";
                    }
                    else
                    {

                        int selectedItemIndex = selectRandomElement2(selectall); // ここでランダムに選んで削除
                    }
                }
                num3 = 0;
                cout << "\n対象:\n----------\n";
                for (const string &nowitem : selectlist)
                {
                    cout << num3 << "]" << nowitem << endl;
                    num3++;
                }
                cout << "----------\n";
                cout << "続行するにはエンターキーを押してください・・・";
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cin.get();
                selectlist.clear();
            }
            break;
        case 41:

            selectRandomElement3(items_copy);
             resetselect = 0;
            cout << "\nこのまま指定を完了しますか？(1で実行、それ以外未完了で続行)\n"
                 << "選択: ";
            cin >> resetselect;
            if (resetselect == 1)
            {
                num3 = 0;
                cout << "\n対象:\n----------\n";
                for (const string &nowitem : selectlist)
                {
                    cout << num3 << "]" << nowitem << endl;
                    num3++;
                }
                cout << "----------\n";
                cout << "続行するにはエンターキーを押してください・・・";
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cin.get();
                selectlist.clear();
            }
            else
            {
                cout << "キャンセルされました。\n";
                cout << "続行するにはエンターキーを押してください・・・";
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cin.get();
            }

            break;
        case 5: // 5:指定消去
            AntlselectElement(enditems);
            cout << "続行するにはエンターキーを押してください・・・";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin.get();
            break;
        case 6: // 6:王様指定
            if (items_people.empty())
            {
                cout << "=======リストが空です。=======\n";
                cout << "続行するにはエンターキーを押してください・・・";
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cin.get();
            }
            else
            {
                select_people.clear();
                int selectedItemIndex = selectRandomElement_people(items_people); // ここでランダムに選んで削除

                cout << "\n王様指定結果:\n----------\n";
                for (const string &nowitem : select_people)
                {
                    cout << "-]" << nowitem << endl;
                }
                cout << "----------\n";
                cout << "続行するにはエンターキーを押してください・・・";
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cin.get();
            }
            break;
        case 7: // 7:王様指定確認・削除
            peopleinfo();
            break;
        case 8: // 8:指定消去&リスト反映
            resetselect = 0;
            cout << "\n指定を全消去し、リストを反映しますがよろしいでしょうか？(0でキャンセル、1で実行)\n"
                 << "選択: ";
            cin >> resetselect;
            if (resetselect == 0)
            {
                break;
            }
            else if (resetselect == 1)
            {
                selectlist.clear();
                enditems.clear();
                items_copy = items; // コピーコンストラクタ
            }
            else
            {
                cout << "有効でない値が入力されたためキャンセルされました。\n";
                cout << "続行するにはエンターキーを押してください・・・";
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cin.get();
            }
            break;
        case 9: // 9:王様指定削除&リスト読み込み
            resetselect = 0;
            cout << "\n王様指定を全消去し、リストを反映しますがよろしいでしょうか？(0でキャンセル、1で実行)\n"
                 << "選択: ";
            cin >> resetselect;
            if (resetselect == 0)
            {
                break;
            }
            else if (resetselect == 1)
            {
                select_people.clear();
                endPeople.clear();
                items_people = items; // コピーコンストラクタ
            }
            else
            {
                cout << "有効でない値が入力されたためキャンセルされました。\n";
                cout << "続行するにはエンターキーを押してください・・・";
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cin.get();
            }
            break;
        case 0:     // 7:戻る
            return; // Whileループを抜ける
        default:
            select = 99;
            break;
        }
    }

    ctrl();
}

// ４じょーほー
void info()
{
    cout << "テスト";
    initializeList(items);
    ctrl();
}

// ５終了
void end()
{
    exit(0);
}

// メイン。
int main()
{
    system("cls");
    ctrl();
    return 0;
}

void stainfo()
{
    system("cls");
    cout << "----リリン式ルーレットシステム----\n"
         << "--var:0.0.2--\n";
}

int chest()
{
    int num = 0;
    cout << "\n現在のリストの内容:\n----------\n";
    for (const string &item : items)
    {
        cout << num << "]" << item << endl;
        num++;
    }
    cout << "----------\n\n";

    return 0;
}

int random_items()
{
    int num = 0;
    cout << "\n現在のリストの内容:\n----------\n";
    for (const string &item : items)
    {
        cout << num << "]" << item << endl;
        num++;
    }
    cout << "----------\n\n";

    return 0;
};
// ========================================
// ========================================
// ========================================
