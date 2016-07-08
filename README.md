## 北理工数据挖掘作业02

> 作业提交时间：2016.7.8

### 学生信息
- 姓名：宁小东
- 学号：2120151024
- 邮箱：xdning@bit.edu.cn

### 数据集

UCI的“急性炎症”数据集

### 处理步骤

UCI炎症数据集的处理步骤如下：  
  1. 使用整型变量代替{yes, no}取值，对原数据进行处理。  
  2. 使用Apriori算法计算频繁项集。  
  3. 去除不含有相关属性的冗余规则。  
  4. 计算关联规则，并对其进行评价和可视化。  

### 包含文件

- data_processing.cpp 对原数据集进行处理
- rule_mining.cpp 计算频繁项集并挖掘和评价关联规则
- raw.txt 未处理的数据集
- processed.txt 处理后的数据集
- Analytic_report.pdf 分析报告