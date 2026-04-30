package com.lab.borrow.web.controller;

import com.lab.borrow.common.PageResult;
import com.lab.borrow.domain.Const;
import com.lab.borrow.entity.Category;
import com.lab.borrow.entity.Device;
import com.lab.borrow.service.CategoryService;
import com.lab.borrow.service.DeviceService;
import com.lab.borrow.web.dto.DeviceForm;
import org.springframework.stereotype.Controller;
import org.springframework.validation.BindingResult;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.PathVariable;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestParam;

import javax.annotation.Resource;
import javax.servlet.http.HttpServletRequest;
import javax.validation.Valid;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

@Controller
public class DeviceWebController {
    @Resource
    private DeviceService deviceService;

    @Resource
    private CategoryService categoryService;

    @GetMapping("/devices")
    public String list(@RequestParam(value = "categoryId", required = false) Integer categoryId,
                       @RequestParam(value = "keyword", required = false) String keyword,
                       @RequestParam(value = "page", required = false, defaultValue = "1") int page,
                       @RequestParam(value = "size", required = false, defaultValue = "10") int size,
                       HttpServletRequest request) {
        PageResult<Device> devicePage = deviceService.page(categoryId, keyword, page, size);
        List<Category> categories = categoryService.listAll();
        Map<Integer, String> categoryMap = toCategoryMap(categories);

        request.setAttribute("devicePage", devicePage);
        request.setAttribute("categories", categories);
        request.setAttribute("categoryMap", categoryMap);
        request.setAttribute("categoryId", categoryId);
        request.setAttribute("keyword", keyword == null ? "" : keyword);
        return "device_list";
    }

    @GetMapping("/devices/{id}")
    public String detail(@PathVariable("id") Integer id, HttpServletRequest request) {
        Device device = deviceService.getById(id);
        List<Category> categories = categoryService.listAll();
        Map<Integer, String> categoryMap = toCategoryMap(categories);
        request.setAttribute("device", device);
        request.setAttribute("categoryMap", categoryMap);
        return "device_detail";
    }

    @GetMapping("/admin/devices/new")
    public String newForm(HttpServletRequest request) {
        request.setAttribute("form", new DeviceForm());
        request.setAttribute("categories", categoryService.listAll());
        request.setAttribute("statuses", allowedStatuses());
        request.setAttribute("action", "/admin/devices");
        return "device_form";
    }

    @PostMapping("/admin/devices")
    public String create(@Valid DeviceForm form, BindingResult bindingResult, HttpServletRequest request) {
        if (bindingResult.hasErrors()) {
            request.setAttribute("message", bindingResult.getFieldError() == null ? "参数错误" : bindingResult.getFieldError().getDefaultMessage());
            request.setAttribute("form", form);
            request.setAttribute("categories", categoryService.listAll());
            request.setAttribute("statuses", allowedStatuses());
            request.setAttribute("action", "/admin/devices");
            return "device_form";
        }
        Device device = new Device();
        device.setDeviceName(form.getDeviceName());
        device.setDeviceModel(form.getDeviceModel());
        device.setCategoryId(form.getCategoryId());
        device.setLocation(form.getLocation());
        device.setPurchaseDate(form.getPurchaseDate());
        device.setStatus(form.getStatus());
        device.setMaxBorrowDays(form.getMaxBorrowDays());
        deviceService.create(device);
        return "redirect:/devices";
    }

    @GetMapping("/admin/devices/{id}/edit")
    public String editForm(@PathVariable("id") Integer id, HttpServletRequest request) {
        Device device = deviceService.getById(id);
        DeviceForm form = toForm(device);
        request.setAttribute("form", form);
        request.setAttribute("categories", categoryService.listAll());
        request.setAttribute("statuses", allowedStatuses());
        request.setAttribute("action", "/admin/devices/" + id);
        return "device_form";
    }

    @PostMapping("/admin/devices/{id}")
    public String update(@PathVariable("id") Integer id, @Valid DeviceForm form, BindingResult bindingResult, HttpServletRequest request) {
        if (bindingResult.hasErrors()) {
            request.setAttribute("message", bindingResult.getFieldError() == null ? "参数错误" : bindingResult.getFieldError().getDefaultMessage());
            request.setAttribute("form", form);
            request.setAttribute("categories", categoryService.listAll());
            request.setAttribute("statuses", allowedStatuses());
            request.setAttribute("action", "/admin/devices/" + id);
            return "device_form";
        }
        Device device = new Device();
        device.setDeviceId(id);
        device.setDeviceName(form.getDeviceName());
        device.setDeviceModel(form.getDeviceModel());
        device.setCategoryId(form.getCategoryId());
        device.setLocation(form.getLocation());
        device.setPurchaseDate(form.getPurchaseDate());
        device.setStatus(form.getStatus());
        device.setMaxBorrowDays(form.getMaxBorrowDays());
        deviceService.update(device);
        return "redirect:/devices/" + id;
    }

    @PostMapping("/admin/devices/{id}/delete")
    public String delete(@PathVariable("id") Integer id) {
        deviceService.delete(id);
        return "redirect:/devices";
    }

    private Map<Integer, String> toCategoryMap(List<Category> categories) {
        Map<Integer, String> map = new HashMap<>();
        for (Category c : categories) {
            map.put(c.getCategoryId(), c.getCategoryName());
        }
        return map;
    }

    private String[] allowedStatuses() {
        return new String[]{Const.DEVICE_STATUS_AVAILABLE, Const.DEVICE_STATUS_MAINTENANCE, Const.DEVICE_STATUS_RETIRED};
    }

    private DeviceForm toForm(Device device) {
        DeviceForm form = new DeviceForm();
        form.setDeviceId(device.getDeviceId());
        form.setDeviceName(device.getDeviceName());
        form.setDeviceModel(device.getDeviceModel());
        form.setCategoryId(device.getCategoryId());
        form.setLocation(device.getLocation());
        form.setPurchaseDate(device.getPurchaseDate());
        form.setStatus(device.getStatus());
        form.setMaxBorrowDays(device.getMaxBorrowDays());
        return form;
    }
}
