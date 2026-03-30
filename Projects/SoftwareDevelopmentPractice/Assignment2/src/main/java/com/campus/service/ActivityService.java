package com.campus.service;

import com.campus.dao.ActivityDao;
import com.campus.entity.Activity;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

import java.util.List;

@Service
public class ActivityService {

    @Autowired
    private ActivityDao activityDao;

    public List<Activity> findAll() {
        return activityDao.findAll();
    }

    public Activity findById(String id) {
        return activityDao.findById(id);
    }

    public List<Activity> findByType(String type) {
        return activityDao.findByType(type);
    }

    public List<Activity> search(String keyword) {
        return activityDao.search(keyword);
    }

    public void save(Activity activity) {
        activityDao.save(activity);
    }

    public void update(Activity activity) {
        activityDao.update(activity);
    }

    public void delete(String id) {
        activityDao.delete(id);
    }

    public void addParticipant(String id, String studentId) {
        // In a real system, you would record the studentId in a join table
        activityDao.addParticipant(id);
    }
}
