import pandas as pd
import matplotlib.pyplot as plt

df = pd.read_csv('output.txt', sep=",", header=None)
df.columns = ["x", "y", "z", "freq"]

plt.figure(figsize=(30, 10))
plt.plot(df['freq'], df['x'])
plt.plot(df['freq'], df['y'])
plt.plot(df['freq'], df['z'])

plt.savefig('plot-fft.pdf')