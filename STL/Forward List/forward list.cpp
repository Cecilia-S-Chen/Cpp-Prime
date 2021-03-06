/*
 * forward list
 *
 * 一、底层数据结构：单向链表
 *
 * 二、特殊之处
 * 1、forward_list不提供返回其大小的操作
 *  计算一个forward_list的长度需要线性的时间，库用户有时无法忍受这样的时间开销。没有size()
 * 2、forward_list是唯一一个在给定位置之后插入新元素的容器。
 *  其他所有STL容器都是在指定位置之前插入元素（除了std::array，它不允许插入）。
 *  forward_list为了在指定节点之前插入新元素，我们必须要先获得插入位置前一个位置的节点，为了获取前面这个节点，需要线性的操作时间。
 *              是在指定位置之后插入新元素，则无需线性时间的查找操作，这样可实现常数时间的插入
 *  forward_list没有提供在尾部进行操作的接口，包括push_back(),pop_back()和emplace_back(),这些操作对单列表来说都至少要花费O(n)来完成
 *
 *
 */

