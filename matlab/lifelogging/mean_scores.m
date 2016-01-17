% part of the solution to Q4
function [Mean] = mean_scores(users, scores)
    Mean = [];
    
    % get a matrix of users and their scores
    A = [users scores];
    
    % find the max user ID
    m = max(users);
    
    % find the length of M
    n = length(M);
    
    % put the user IDs in the matrix to be returned
    Mean(:,1) = [0:m];
    
    % loop through every user ID and compute their mean score
    for i = 0:m
        total = 0;
        days = 0;
        for j = 1:n
            if (users(j) == i)
                days = days + 1;
                total = total + scores(j);
            end
        Mean(i+1,2) = total/days;
    end
end
