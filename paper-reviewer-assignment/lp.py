from ortools.linear_solver import pywraplp

def solve_paper_assignment(data):
    idx = 0
    N = int(data[idx])
    idx += 1
    M = int(data[idx])
    idx += 1
    b = int(data[idx])
    idx += 1

    willing_reviewers = []
    for i in range(N):
        k = int(data[idx])
        idx += 1
        reviewers = []
        for j in range(k):
            reviewers.append(int(data[idx]))
            idx += 1
        willing_reviewers.append(reviewers)

    # Solver
    solver = pywraplp.Solver.CreateSolver('CBC')

    # Variables
    x = {}
    for i in range(N):
        for j in willing_reviewers[i]:
            x[i, j] = solver.BoolVar(f'x[{i},{j}]')

    # Load variables
    load = {}
    for j in range(1, M + 1):
        load[j] = solver.IntVar(0, solver.infinity(), f'load[{j}]')

    # Constraints
    # Each paper must be reviewed by exactly b reviewers
    for i in range(N):
        solver.Add(sum(x[i, j] for j in willing_reviewers[i]) == b)

    # Reviewer load constraints
    for j in range(1, M + 1):
        solver.Add(load[j] == sum(x[i, j] for i in range(N) if j in willing_reviewers[i]))

    # Objective: Minimize the maximum load
    max_load = solver.IntVar(0, solver.infinity(), 'max_load')
    for j in range(1, M + 1):
        solver.Add(max_load >= load[j])

    solver.Minimize(max_load)

    status = solver.Solve()

    result = []
    if status == pywraplp.Solver.OPTIMAL:
        result.append(str(N))
        for i in range(N):
            assigned_reviewers = [j for j in willing_reviewers[i] if x[i, j].solution_value() > 0.5]
            result.append(f"{b} " + ' '.join(map(str, assigned_reviewers)))
    else:
        result.append('No solution found.')

    return '\n'.join(result)

def main():
    file_path = "/content/data.txt"
    with open(file_path, 'r') as file:
        data = file.read().split()
    print(solve_paper_assignment(data))

if __name__ == "__main__":
    main()