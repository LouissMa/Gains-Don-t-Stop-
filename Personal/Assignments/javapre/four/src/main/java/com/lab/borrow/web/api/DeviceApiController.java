package com.lab.borrow.web.api;

import com.lab.borrow.common.PageResult;
import com.lab.borrow.common.Result;
import com.lab.borrow.entity.Device;
import com.lab.borrow.service.DeviceService;
import com.lab.borrow.web.dto.DeviceForm;
import org.springframework.validation.BindingResult;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.PathVariable;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.RequestBody;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.bind.annotation.RestController;

import javax.validation.Valid;

@RestController
@RequestMapping("/api/devices")
public class DeviceApiController {
    private final DeviceService deviceService;

    public DeviceApiController(DeviceService deviceService) {
        this.deviceService = deviceService;
    }

    @GetMapping("/page")
    public Result<PageResult<Device>> page(@RequestParam(value = "categoryId", required = false) Integer categoryId,
                                           @RequestParam(value = "keyword", required = false) String keyword,
                                           @RequestParam(value = "page", required = false, defaultValue = "1") int page,
                                           @RequestParam(value = "size", required = false, defaultValue = "10") int size) {
        return Result.success(deviceService.page(categoryId, keyword, page, size));
    }

    @GetMapping("/{id}")
    public Result<Device> get(@PathVariable("id") Integer id) {
        return Result.success(deviceService.getById(id));
    }

    @PostMapping
    public Result<Device> create(@Valid @RequestBody DeviceForm form, BindingResult bindingResult) {
        if (bindingResult.hasErrors()) {
            return Result.bizFail(bindingResult.getFieldError() == null ? "参数错误" : bindingResult.getFieldError().getDefaultMessage());
        }
        Device device = toEntity(null, form);
        return Result.success(deviceService.create(device));
    }

    @PostMapping("/{id}")
    public Result<Device> update(@PathVariable("id") Integer id, @Valid @RequestBody DeviceForm form, BindingResult bindingResult) {
        if (bindingResult.hasErrors()) {
            return Result.bizFail(bindingResult.getFieldError() == null ? "参数错误" : bindingResult.getFieldError().getDefaultMessage());
        }
        Device device = toEntity(id, form);
        return Result.success(deviceService.update(device));
    }

    @PostMapping("/{id}/delete")
    public Result<Void> delete(@PathVariable("id") Integer id) {
        deviceService.delete(id);
        return Result.success(null);
    }

    private Device toEntity(Integer id, DeviceForm form) {
        Device device = new Device();
        device.setDeviceId(id);
        device.setDeviceName(form.getDeviceName());
        device.setDeviceModel(form.getDeviceModel());
        device.setCategoryId(form.getCategoryId());
        device.setLocation(form.getLocation());
        device.setPurchaseDate(form.getPurchaseDate());
        device.setStatus(form.getStatus());
        device.setMaxBorrowDays(form.getMaxBorrowDays());
        return device;
    }
}
