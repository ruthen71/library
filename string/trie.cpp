#include <bits/stdc++.h>
using namespace std;

// trie
// ref:https://algo-logic.info/trie-tree
// ref:https://ei1333.github.io/luzhiled/snippets/structure/trie.html
// アルゴリズムロジックのサイトの実装では各ノードに対応する文字があったが
// オートマトンを考えると自然でないと判断し、辺に文字を割り当てた
// ref先と同じものではない(具体的にはstring_idが増えている(その分遅い))

template <int char_size, int start>
struct trie {
    struct trie_node {
        // int string_id_size;  // 定数倍高速化用
        // string_idへのpush_backをコメントアウトして、searchの戻り値をboolに変えると早くなると思う
        vector<int> child_id;   // 子ノードのid
        vector<int> string_id;  // ノードを通る文字列のid
        vector<int> accept_id;  // 受理状態の文字列のid
        trie_node() : child_id(char_size, -1) {}
    };
    vector<trie_node> nodes;
    trie() { nodes.push_back(trie_node()); }  // 開始ノードを入れる
    void insert(const string &word, int word_id) {
        int node_id = 0;
        for (int i = 0; i < (int)word.size(); i++) {
            const int c = word[i] - start;
            if (nodes[node_id].child_id[c] == -1) {
                nodes[node_id].child_id[c] = (int)nodes.size();
                nodes.push_back(trie_node());
            }
            nodes[node_id].string_id.push_back(word_id);
            node_id = nodes[node_id].child_id[c];  // 次に行く
        }
        nodes[node_id].string_id.push_back(word_id);
        nodes[node_id].accept_id.push_back(word_id);
    }
    void insert(const string &word) { insert(word, (int)nodes[0].string_id.size()); }
    // 条件を満たす文字列のidの集合(vector)を返す
    vector<int> search(const string &word, bool prefix = false) {
        // prefix=trueだとwordがprefixとなる単語すべてが条件を満たすとして扱う
        // prefix=falseだとwordと一致する単語のidを返す(重複がなければサイズ1のベクトルということ)
        int node_id = 0;
        for (int i = 0; i < (int)word.size(); i++) {
            int c = word[i] - start;
            if (nodes[node_id].child_id[c] == -1) {
                return vector<int>();
            }
            node_id = nodes[node_id].child_id[c];
        }
        return (prefix) ? nodes[node_id].string_id : nodes[node_id].accept_id;
    }
    int size() { return ((int)nodes.size()); }                // node数を返す
    int count() { return ((int)nodes[0].string_id.size()); }  // 追加した文字列の個数を返す
};
