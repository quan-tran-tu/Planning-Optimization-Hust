def main():
    import sys
    input = sys.stdin.read
    data = input().split()
    
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
    
    reviewer_load = [0] * (M + 1)
    assignment = [[] for _ in range(N)]
    
    for i in range(N):
        load_list = []
        for reviewer in willing_reviewers[i]:
            load_list.append((reviewer_load[reviewer], reviewer))
        load_list.sort()
        
        for j in range(b):
            chosen_reviewer = load_list[j][1]
            assignment[i].append(chosen_reviewer)
            reviewer_load[chosen_reviewer] += 1
    
    print(N)
    for i in range(N):
        print(b, ' '.join(map(str, assignment[i])))

if __name__ == "__main__":
    main()
