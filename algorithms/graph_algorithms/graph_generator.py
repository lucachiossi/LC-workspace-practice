"""
this script generates graphs in json format

input: <file-name> d|nd <max-node-number> <max-neighbors-per-node> we|nwe
    (<max-edge-weight>)

output: <file-name>.json
"""

import sys
from pathlib import Path
import json
import random
import itertools


def main():
    """main function"""

    # CHECK AND GET COMMAND LINE INPUT
    input_format = str('<file-name> d|nd <max-nodes> <max-neighbors>')
    input_format += str(' we|nwe (<max-edge-weight>)')
    bad_input_message = str('call as: graph_generator.py ') + input_format

    if len(sys.argv) < 6 or len(sys.argv) > 8:
        print('bad input\n{0}'.format(bad_input_message))
        sys.exit()

    output_file_name = Path(sys.argv[1])
    directed = sys.argv[2]

    try:
        int(sys.argv[3])
    except ValueError:
        print('bad max-nodes\n{0}'.format(bad_input_message))
        sys.exit()
    max_nodes = int(sys.argv[3])

    try:
        int(sys.argv[4])
    except ValueError:
        print('bad max-neighbors\n{0}'.format(bad_input_message))
        sys.exit()
    max_neighbors = int(sys.argv[4])

    weighted_edges = sys.argv[5]
    max_edge_weight = 0

    if output_file_name.parent.exists() is False:
        print('bad file-name\n{0}'.format(bad_input_message))
        sys.exit()

    if directed not in ('d', 'nd'):
        print('bad d|nd\n{0}'.format(bad_input_message))
        sys.exit()

    if max_nodes < 1:
        print('bad max_nodes\n{0}'.format(bad_input_message))
        sys.exit()

    if max_neighbors < 0:
        print('bad max_neighbors\n{0}'.format(bad_input_message))
        sys.exit()

    if weighted_edges not in ('we', 'nwe'):
        print('bad we|nwe\n{0}'.format(bad_input_message))
        sys.exit()

    if weighted_edges == 'we':
        if len(sys.argv) != 7:
            print('bad edge-weight'' parameter\n{0}'.format(bad_input_message))
            sys.exit()
        try:
            int(sys.argv[6])
        except ValueError:
            print('bad edge-weight\n{0}'.format(bad_input_message))
            sys.exit()
        max_edge_weight = int(sys.argv[6])
        if max_edge_weight < 1:
            print('bad edge_weight\n{0}'.format(bad_input_message))
            sys.exit()

    # GENERATE GRAPH
    adj_matrix = [['x' for x in range(max_nodes)]for y in range(max_nodes)]

    for row in range(max_nodes):
        neighbors_number = random.randint(1, max_neighbors)
        for _ in itertools.repeat(None, neighbors_number):
            neighbor = -1
            if directed == 'd':
                neighbor = random.randint(row, max_nodes-1)
            else:
                neighbor = random.randint(0, max_nodes-1)
            edge_weight = 1
            if weighted_edges == 'we':
                edge_weight = random.randint(1, max_edge_weight)

            adj_matrix[row][neighbor] = edge_weight

    if directed == 'nd':
        for row in range(max_nodes):
            for col in range(max_nodes):
                if adj_matrix[row][col] != 'x':
                    adj_matrix[col][row] = adj_matrix[row][col]

    # SAVE GRAPH TO FILE
    if output_file_name.exists():
        out = open(str(output_file_name), "w")
        out.write('')
        out.close()

    out = open(str(output_file_name), "a")

    for i in enumerate(adj_matrix):
        print(i[1])

    json.dump(adj_matrix, out)
    out.close()


if __name__ == "__main__":
    main()
