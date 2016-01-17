function [Mean] = mean_scores(users, scores)
    Mean = [];
    A = [users scores];
    m = max(users);
    n = length(users);
    Mean(:,1) = [0:m];
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
