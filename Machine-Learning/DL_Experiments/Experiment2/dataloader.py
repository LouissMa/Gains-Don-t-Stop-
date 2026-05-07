import os
import pandas as pd
from torch.utils.data import Dataset
from nltk.tokenize import word_tokenize
import nltk
nltk.download('punkt')


'''
Mean table Length: 25.305850585058504
Max table Length:40
Mean reference Length: 21.541434143414342
Max reference Length:70
'''


class RestaurantDataset(Dataset):
    def __init__(self, data_path='./data/', mode='train'):
        assert mode in ['train', 'valid', 'test']
        self.mode = mode
        self.data_path = os.path.join(data_path, f'{self.mode}set.csv')

        # read the dataset
        df_data = pd.read_csv(self.data_path)
        self.table = df_data['table']

        self.length = len(self.table)

        if self.mode == 'test':
            self.reference = ['.' for _ in range(self.length)]
        else:
            self.reference = df_data['reference']

        assert len(self.reference) == len(self.table)

    def __len__(self):
        return self.length

    def __getitem__(self, item):
        return self.table[item], self.reference[item]

    def statistics(self):
        mean_table = 0
        max_table = 0
        mean_reference = 0
        max_reference = 0

        for idx in range(self.length):
            table_token = word_tokenize(self.table[idx])
            reference_token = word_tokenize(self.reference[idx])

            mean_table = mean_table + len(table_token)
            mean_reference = mean_reference + len(reference_token)

            if len(table_token) > max_table:
                max_table = len(table_token)

            if len(reference_token) > max_reference:
                max_reference = len(reference_token)

        print(f'Mean table Length: {mean_table/self.length}')
        print(f'Max table Length:{max_table}')
        print(f'Mean reference Length: {mean_reference / self.length}')
        print(f'Max reference Length:{max_reference}')



'''_test = RestaurantDataset(mode='test')
# _test.statistics()
a, b = _test.__getitem__(5)

print(a)
print(b)
print(word_tokenize(a))
print(word_tokenize(b))
'''