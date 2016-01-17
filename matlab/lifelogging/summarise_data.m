% part of the solution to tut2 Q4
function [S] = summarise_data(A,B)

    % create the struct to be returned
    S = struct
    
    % create vectors of users and scores
    A_users = A.data(:,3);
    B_users = B.data(:,6);
    A_steps = A.data(:,2);
    B_act = lifelogging.activity_scores(B);
    
    % find the max overall user_ID
    m = max(max(A_users),max(B_users));
    
    % add the IDs to the struct
    S.ids = {0:m};
    
    % vectors of mean scores
    steps = lifelogging.mean_scores(A_users,A_steps);
    act = lifelogging.mean_scores(B_users,B_act);
    
    % attempt to solve the issue of different user_IDs in A and B
    i = 1;
    j = 1;
    while (i ~= length(steps) & j ~= length(act))
       if (steps(i,1) == act(j,1))
          i = i + 1;
          j = j + 1;
       elseif (steps(i,1) < act(j,1))
           T = [steps(i,1),0];
           act = cat(1, act([0:j-1],:), T, act([j:length(act)],:));
           i = i + 1;
       elseif (steps(i,1) > act(j,1))
           T = [act(j,1),0];
           steps = cat(1, steps([0:i-1],:), T, steps([i:length(steps)],:));
           j = j + 1;
       end
    end
    
    % add the scores to the struct
    S.steps = steps;
    S.act = act;
end
