#pragma once

#include <functional>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace strukdat {

template <typename VertexType>
class graph {
  /**
   * @brief Tipe data dari adjacency list. (BOLEH DIUBAH)
   *
   * @note
   * Misal:
   *
   * adj_list_type adj_list =
   *
   * | map key  |             list_type
   * | - - - -  | - - - - - - - - - - - - - - - - -
   * | vertex_1 | vertex_2, vertex_5, vertex_4, ...
   * | vertex_2 | vertex_1, vertex_3
   * |   ...    |           ...
   *
   * maka,
   *
   * adj_list[vertex_2]; // { vertex_1, vertex_3 }
   */
  using list_type = std::unordered_set<VertexType>;
  using adj_list_type = std::unordered_map<VertexType, list_type>;

 public:
  /**
   * @brief Default constructor.
   *
   * @constructor
   */
  graph() {}

  /**
   * @brief Menambahkan vertex baru pada graph
   *
   * @param val nilai dari vertex yang akan ditambahkan
   */
  void add_vertex(const VertexType &val) {
    // Contoh implementasi. (BOLEH DIUBAH)
    // inisialisasi _adj_list[val] dengan list kosong
    _adj_list.insert(std::make_pair(val, list_type()));
  }

  void remove_vertex(const VertexType &val) {
    if (_adj_list.find(val) == _adj_list.end())
    {
      return;
    }
    
    _adj_list.erase(val);

    for (auto &vertex : _adj_list)
    {
      if (vertex.second.find(val) != vertex.second.end())
      {
        vertex.second.erase(val);
      }
    }
  }

  /**
   * @brief Menambahkan edge baru dari 2 vertex
   *
   * @param val1 nilai vertex 1
   * @param val2 nilai vertex 2
   */
  void add_edge(const VertexType &val1, const VertexType val2) {
    if (_adj_list.find(val1) != _adj_list.end() && _adj_list.find(val2) != _adj_list.end())
    {
      _adj_list[val1].insert(val2);
      _adj_list[val2].insert(val1);
    }
  }

  /**
   * @brief Menghapus vertex baru pada graph
   *
   * @param val nilai dari vertex yang akan dihapus
   */
  void remove_edge(const VertexType &val1, const VertexType &val2) {
    if (_adj_list.find(val1) == _adj_list.end() || _adj_list.find(val1) == _adj_list.end())
    {
      return;
    }

    if (_adj_list[val1].find(val2) == _adj_list[val1].end())
    {
      return;
    }
    _adj_list[val1].erase(val2);
    _adj_list[val2].erase(val1);
  }

  /**
   * @brief Mengembalikan ordo dari graph.
   *
   * @note
   * Ordo graph adalah jumlah node pada graph
   *
   * @return jumlah node pada graph
   */
  size_t order() const {
    return _adj_list.size();
  }

  /**
   * @brief Cek apakah 2 vertex bertetangga satu sama lain.
   *
   * @param val1 nilai vertex 1
   * @param val2 nilai vertex 2
   *
   * @return vertex-vertex saling bertetangga
   */
  bool is_edge(const VertexType &val1, const VertexType &val2) const {
    if (_adj_list.find(val1) == _adj_list.end() || _adj_list.find(val1) == _adj_list.end())
    {
      return 0; 
    }

    if (_adj_list.at(val1).find(val2) == _adj_list.at(val1).end() || _adj_list.at(val2).find(val1) == _adj_list.at(val1).end())
    {
      return 0;
    }

    return 1;
  }

  /**
   * @brief Melakukan BFS traversal pada graph
   *
   * @param root vertex awal
   * @param func fungsi yang akan dieksekusi pada setiap vertex
   */
  void bfs(const VertexType &root,
           std::function<void(const VertexType &)> func) const 
           {
    std::unordered_map<VertexType, bool> came;
    for (auto &vertex : _adj_list){
      came.insert(std::make_pair(vertex.first, false));
    }
    std::vector<VertexType> queue;
    queue.push_back(root);
    came[root] = true;
    while(!queue.empty()){
      VertexType temp = queue.front();
      queue.erase(queue.begin());
      func(temp);
      for (auto i : _adj_list.at(temp))
      {
        if (!came[i]){
          came[i] = true;
          queue.push_back(i);
        }
      }
    }
  }

  /**
   * @brief Melakukan DFS traversal pada graph
   *
   * @param root vertex awal
   * @param func fungsi yang akan dieksekusi pada setiap vertex
   */
  void dfs(const VertexType &root,
           std::function<void(const VertexType &)> func) const {
    std::unordered_map<VertexType, bool> came;
    for (auto &vertex : _adj_list){
      came.insert(std::make_pair(vertex.first, false));
    }
    std::vector<VertexType> stack;
    VertexType temp = root;
    stack.insert(stack.begin(), temp);
    while (!stack.empty()){
      if (!came[temp]){
        came[temp] = true;
        func(temp);
      }
      auto i = _adj_list.at(temp).begin();
      for (; i != _adj_list.at(temp).end(); ++i)
      {
        if (!came[*i]){
          temp = *i;
          stack.insert(stack.begin(), temp);
        }
      }
      if (i == _adj_list.at(temp).end())
      {
        temp = stack.front();
        stack.erase(stack.begin());
      }
    }
  }

 private:
  /**
   * @brief Adjacency list dari graph
   *
   * @private
   */
  adj_list_type _adj_list;
};

}  // namespace strukdat
