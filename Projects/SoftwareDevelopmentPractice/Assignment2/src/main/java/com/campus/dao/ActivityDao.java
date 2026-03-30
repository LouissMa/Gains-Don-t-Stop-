package com.campus.dao;

import com.campus.entity.Activity;
import org.springframework.stereotype.Repository;

import java.util.*;
import java.util.concurrent.ConcurrentHashMap;
import java.util.stream.Collectors;

@Repository
public class ActivityDao {
    private static final Map<String, Activity> activities = new ConcurrentHashMap<>();

    static {
        // Mock data
        Calendar cal = Calendar.getInstance();
        cal.add(Calendar.DAY_OF_MONTH, 5);
        Date start1 = cal.getTime();
        cal.add(Calendar.HOUR_OF_DAY, 4);
        Date end1 = cal.getTime();

        activities.put("ACT001", new Activity("ACT001", "校园篮球赛", "一年一度的校园篮球赛", "体育部", "体育", 
                start1, end1, "体育馆", 100, 56, "报名中"));

        cal = Calendar.getInstance();
        cal.add(Calendar.DAY_OF_MONTH, 10);
        Date start2 = cal.getTime();
        cal.add(Calendar.HOUR_OF_DAY, 2);
        Date end2 = cal.getTime();

        activities.put("ACT002", new Activity("ACT002", "AI技术讲座", "ChatGPT与AI未来", "计算机学院", "学术", 
                start2, end2, "报告厅A", 200, 180, "报名中"));
    }

    public List<Activity> findAll() {
        return new ArrayList<>(activities.values());
    }

    public Activity findById(String id) {
        return activities.get(id);
    }

    public void save(Activity activity) {
        if (activity.getActivityId() == null || activity.getActivityId().isEmpty()) {
            activity.setActivityId("ACT" + (activities.size() + 1));
        }
        activities.put(activity.getActivityId(), activity);
    }

    public void update(Activity activity) {
        activities.put(activity.getActivityId(), activity);
    }

    public void delete(String id) {
        activities.remove(id);
    }

    public List<Activity> findByType(String type) {
        return activities.values().stream()
                .filter(a -> a.getType().equalsIgnoreCase(type))
                .collect(Collectors.toList());
    }

    public List<Activity> search(String keyword) {
        return activities.values().stream()
                .filter(a -> a.getTitle().contains(keyword) || a.getDescription().contains(keyword))
                .collect(Collectors.toList());
    }

    public void addParticipant(String id) {
        Activity activity = activities.get(id);
        if (activity != null) {
            activity.setCurrentParticipants(activity.getCurrentParticipants() + 1);
        }
    }
}
