# [Developing] Utils in C

## 1. 介绍

打算写点 C 项目的工具库，省的自己还要 重新写一遍，尤其是链表这个东西，从 高三 写到 大学毕业，都写吐了

## 2. 工具

0. [logs](./logs/logs.h)
这个是我拿来排错的
1. [array](./array/array.h)
我需要这个自定义的数组，一是 C 中的数组是没有 **长度** 字段的，二是容易和 **地址** 混淆
2. [optional](./optional/optional.h)
错误处理 类型，与 Rust 的 Option 类似
3. [result](./result/result.h)
错误处理 类型，与 Rust 的 Result 类似
4. [list](./list/list.h)
链表类型
