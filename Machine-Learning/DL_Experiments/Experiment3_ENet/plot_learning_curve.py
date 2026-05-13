import pandas as pd
import matplotlib.pyplot as plt

#------------------------------------------实验5：根据训练生成的training_history.csv文件，将其进行可视化，将训练生成的SCV文件读入------------------------------------------
df = pd.read_csv("./results/training_history.csv")                        #在此填空

plt.figure(figsize=(10,4))
plt.subplot(1,2,1)
plt.plot(df['Epoch'], df['Train Loss'], label='Train Loss')
plt.plot(df['Epoch'], df['Val Loss'], label='Val Loss')
plt.legend()
plt.title('Loss')
plt.subplot(1,2,2)
plt.plot(df['Epoch'], df['Train Dice'], label='Train Dice')
plt.plot(df['Epoch'], df['Val Dice'], label='Val Dice')
plt.legend()
plt.title('Dice')
plt.savefig("./results/learning_curves.png")
plt.show()