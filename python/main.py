import os.path
import matplotlib.pyplot as plot

output_directory = os.path.abspath("../output/")

def display_results(x_values: list[float], y_values: list[float]):
    figure, axes = plot.subplots()
    axes.plot(x_values, y_values)
    plot.show()

if __name__=="__main__":
    target_file = os.path.join(output_directory, "radial_distribution.data")

    first = True
    x_values = []
    y_values = []
    with open(target_file, "r") as f:
        for line in f.readlines():
            if line.startswith("Time:0") or line == "":
                if first:
                    first = False
                    continue
                else:
                    break

            line_data = line.split(" ")
            x_values.append(float(line_data[0]))
            y_values.append(float(line_data[1]))

    display_results(x_values, y_values)
    print("Finished Reading")