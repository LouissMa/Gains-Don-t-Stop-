package com.campus.controller;

import com.campus.entity.Activity;
import com.campus.entity.Result;
import com.campus.service.ActivityService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.*;

import java.util.List;
import java.util.Map;

@RestController
@RequestMapping("/api/activities")
public class ActivityApiController {

    @Autowired
    private ActivityService activityService;

    @GetMapping
    public Result<List<Activity>> getAllActivities(
            @RequestParam(required = false) String type,
            @RequestParam(required = false) String keyword) {
        
        List<Activity> activities;
        
        if (keyword != null && !keyword.isEmpty()) {
            activities = activityService.search(keyword);
        } else if (type != null && !type.isEmpty()) {
            activities = activityService.findByType(type);
        } else {
            activities = activityService.findAll();
        }
        
        return Result.success(activities);
    }

    @GetMapping("/{id}")
    public Result<Activity> getActivityById(@PathVariable String id) {
        Activity activity = activityService.findById(id);
        if (activity != null) {
            return Result.success(activity);
        }
        return Result.error("活动不存在");
    }

    @PostMapping
    public Result<String> createActivity(@RequestBody Activity activity) {
        activity.setStatus("报名中");
        activity.setCurrentParticipants(0);
        activityService.save(activity);
        return Result.success("活动创建成功");
    }

    @PutMapping("/{id}")
    public Result<String> updateActivity(@PathVariable String id, 
                                         @RequestBody Activity activity) {
        Activity existing = activityService.findById(id);
        if (existing == null) {
            return Result.error("活动不存在");
        }
        activity.setActivityId(id);
        activityService.update(activity);
        return Result.success("活动更新成功");
    }

    @DeleteMapping("/{id}")
    public Result<String> deleteActivity(@PathVariable String id) {
        activityService.delete(id);
        return Result.success("活动删除成功");
    }

    @PostMapping("/{id}/join")
    public Result<String> joinActivity(@PathVariable String id,
                                       @RequestBody Map<String, String> request) {
        String studentId = request.get("studentId");
        
        Activity activity = activityService.findById(id);
        if (activity == null) {
            return Result.error("活动不存在");
        }
        
        if ("已结束".equals(activity.getStatus())) {
            return Result.error("活动已结束，无法报名");
        }
        
        if (activity.getCurrentParticipants() >= activity.getMaxParticipants()) {
            return Result.error("活动人数已满");
        }
        
        activityService.addParticipant(id, studentId);
        return Result.success("报名成功！");
    }
}
