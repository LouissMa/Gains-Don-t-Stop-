# 参考文献审查记录

审查对象：`references/library.bib/DL期末/DL期末.bib`

审查依据：BibTeX 元数据、所附 PDF 首页、论文 DOI/出版信息，以及课程要求：

- 参考文献不少于 8 篇；
- 2024—2026 年文献不少于 4 篇；
- 文献必须真实，正文引用与文末条目必须对应；
- 建议优先使用正式期刊或会议论文，预印本应如实标注。

## 总体结论

当前文献库共14条记录。排除来源信息不完整、不建议使用的2018年Li等综述后，建议正文使用13篇。无需将Zotero库中所有文献强行列入参考文献。

按2024—2026年统计，并且不将出版年份存在争议的Jing等论文计入，正文已经使用以下5篇近三年文献：

1. Wu等，LLM推荐综述，2024年，arXiv；
2. Wang等，生成式推荐，2024年，arXiv；
3. Raza等，推荐系统综述，2025年，arXiv；
4. Gheewala等，深度推荐系统综述，2025年，正式期刊；
5. Zhang等，鲁棒推荐系统综述，2026年，ACM Computing Surveys正式期刊。

因此，按照课程“近3年文献不少于4篇”的文字要求，当前正文已经满足，实际数量为5篇。若教师额外要求近三年文献全部为正式期刊或会议论文，则仍有3篇为arXiv预印本；原作业文档并未明确禁止使用预印本。

## 逐条审查

| 序号 | 文献 | 年份 | 类型 | 审查结论 | 建议用途 |
|---|---|---:|---|---|---|
| 1 | Sarwar et al., Item-based Collaborative Filtering Recommendation Algorithms | 2001 | WWW 会议论文 | 真实、信息完整，可用 | 传统协同过滤相关工作 |
| 2 | Koren et al., Matrix Factorization Techniques for Recommender Systems | 2009 | IEEE Computer | 真实、信息完整，可用 | 矩阵分解理论背景 |
| 3 | He et al., Neural Collaborative Filtering | 2017 | WWW 会议论文 | 真实、与本项目最核心 | NeuMF 方法与模型结构 |
| 4 | Guo et al., DeepFM | 2017 | 当前记录为 arXiv | 论文真实，但条目不够规范 | 深度推荐背景；建议改成 IJCAI 会议版本 |
| 5 | Harper and Konstan, The MovieLens Datasets: History and Context | 2016 | ACM TiiS | 真实、信息完整，可用 | MovieLens 数据集介绍 |
| 6 | Wu et al., A Survey on Large Language Models for Recommendation | 2024 | arXiv 预印本 | 真实，可计近三年，但不是本实验核心 | 相关工作和未来展望 |
| 7 | Jing et al., Contrastive Self-supervised Learning in Recommender Systems: A Survey | 2023 | ACM TOIS | 真实、正式期刊；BibTeX 年份需修正 | 自监督推荐相关工作，不计 2024—2026 |
| 8 | Li et al., A Survey on Deep Neural Networks in Collaborative Filtering Recommendation Systems | 2018 | 来源信息不完整 | 风险较高，不建议作为核心引用 | 删除或替换 |
| 9 | Raza et al., A Comprehensive Review of Recommender Systems | 2025 | arXiv 预印本 | 真实，可计近三年；应如实标注预印本 | 推荐系统总体综述 |
| 10 | Wang et al., Generative Recommendation | 2024 | arXiv 预印本 | 真实，可计近三年，但与 NeuMF 实验关系较弱 | 生成式推荐趋势与展望 |
| 11 | Gheewala et al., In-depth Survey: Deep Learning in Recommender Systems | 2025 | Neural Computing and Applications | 真实、正式期刊、近三年核心文献 | 深度推荐相关工作 |

## 必须修正的元数据

1. Jing 等论文的 PDF 推荐引用格式显示为 2023 年，不能因 Zotero 中记录为 2024 年而计入近三年文献。
2. DeepFM 应优先改为正式 IJCAI 2017 会议论文条目，避免仅引用 arXiv 版本。
3. Li 等 2018 年综述缺少明确期刊、会议、DOI 等信息，来源质量和可核验性不足，建议移出最终参考文献。
4. Wu、Raza、Wang 三篇当前条目均为 arXiv，应在最终参考文献中保留 arXiv 编号，不应伪装成正式期刊论文。
5. 最终写作时只列正文中实际引用的文献，不能为了满足数量而把未引用文献堆在文末。

## 推荐的正文分工

- 第 1 章背景：Raza、Gheewala、Harper。
- 第 2 章传统推荐：Sarwar、Koren。
- 第 2 章深度推荐：He、Guo、Gheewala、Jing。
- 第 2 章前沿研究与第 5 章展望：Wu、Wang。
- 第 3 章方法：重点引用 He；数据集部分引用 Harper。
- 第 4 章实验：引用 He 和 Harper，并引用本项目真实代码、配置和实验记录，不用文献中的结果替代本项目结果。

## 最稳妥的补充方案

为了避免教师不认可 arXiv 导致“近三年文献不足”，建议后续再加入 3 篇与以下主题直接相关的 2024—2026 年正式期刊或会议论文：

- 神经协同过滤或深度协同过滤；
- 推荐系统中的对比学习、自监督学习；
- 深度推荐系统综述或电影推荐应用。

新增文献应具有可核验的 DOI、期刊卷期或正式会议名称。
