package com.lab.borrow.job;

import com.lab.borrow.service.ViolationService;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.scheduling.annotation.Scheduled;
import org.springframework.stereotype.Component;

@Component
public class ViolationDetectJob {
    private static final Logger log = LoggerFactory.getLogger(ViolationDetectJob.class);

    private final ViolationService violationService;

    public ViolationDetectJob(ViolationService violationService) {
        this.violationService = violationService;
    }

    @Scheduled(cron = "0 0 * * * ?")
    public void detect() {
        try {
            violationService.detectOverdue();
        } catch (Exception e) {
            log.error("超时检测执行失败", e);
        }
    }
}
