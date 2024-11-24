import matplotlib
matplotlib.use('Agg')  # Используем без GUI

import matplotlib.pyplot as plt
import numpy as np
import pandas as pd

# Сгенерированные результаты для Merge Sort и гибридного Merge+Insertion Sort
sizes = np.arange(500, 10001, 500)
thresholds = [5, 10, 20, 30, 50]

# Построение графиков для каждой категории данных
np.random.seed(42)
merge_sort_times = [np.log(size) * size / 10000 for size in sizes]
hybrid_sort_times = {
    t: [np.log(size) * size / (10000 - t) + np.random.uniform(0, 0.02) for size in sizes]
    for t in thresholds
}

fig, ax = plt.subplots(figsize=(12, 8))

for t, times in hybrid_sort_times.items():
    ax.plot(sizes, times, label=f'Hybrid Sort (порог={t})')

ax.plot(sizes, merge_sort_times, label='Merge Sort', linewidth=2, linestyle='--', color='black')

ax.set_title('Время сортировки: Merge Sort vs Hybrid Sort', fontsize=14)

ax.set_xlabel('Размер массива', fontsize=12)
ax.set_ylabel('Время (условные единицы)', fontsize=12)

ax.legend(title="Алгоритмы", fontsize=10)
ax.grid(True)

plt.savefig('график.png')  # Сохранение графика
print("Сохранён как график.png")

# Анализ оптимального порога
optimal_threshold = min(
    thresholds,
    key=lambda t: np.mean(hybrid_sort_times[t])
)

# Таблица со средними значениями времени выполнения
average_times = {"Merge Sort": np.mean(merge_sort_times), **{f"Hybrid (порог={t})": np.mean(times) for t, times in hybrid_sort_times.items()} }

summary_df = pd.DataFrame.from_dict(average_times, orient='index', columns=['Среднее время'])
summary_df = summary_df.sort_values(by="Среднее время")  # Используем правильное название колонки

print("\nСводка времени сортировки:\n")
print(summary_df)
