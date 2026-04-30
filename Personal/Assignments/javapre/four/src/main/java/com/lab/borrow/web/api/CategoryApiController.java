package com.lab.borrow.web.api;

import com.lab.borrow.common.Result;
import com.lab.borrow.entity.Category;
import com.lab.borrow.service.CategoryService;
import com.lab.borrow.web.dto.CategoryForm;
import org.springframework.validation.BindingResult;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.PathVariable;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.RequestBody;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.bind.annotation.RestController;

import javax.validation.Valid;
import java.util.List;

@RestController
@RequestMapping("/api/categories")
public class CategoryApiController {
    private final CategoryService categoryService;

    public CategoryApiController(CategoryService categoryService) {
        this.categoryService = categoryService;
    }

    @GetMapping
    public Result<List<Category>> list(@RequestParam(value = "parentId", required = false) Integer parentId) {
        if (parentId == null) {
            return Result.success(categoryService.listAll());
        }
        return Result.success(categoryService.listByParentId(parentId));
    }

    @GetMapping("/{id}")
    public Result<Category> get(@PathVariable("id") Integer id) {
        return Result.success(categoryService.getById(id));
    }

    @PostMapping
    public Result<Category> create(@Valid @RequestBody CategoryForm form, BindingResult bindingResult) {
        if (bindingResult.hasErrors()) {
            return Result.bizFail(bindingResult.getFieldError() == null ? "参数错误" : bindingResult.getFieldError().getDefaultMessage());
        }
        Category category = new Category();
        category.setCategoryName(form.getCategoryName());
        category.setParentId(form.getParentId());
        category.setDescription(form.getDescription());
        return Result.success(categoryService.create(category));
    }

    @PostMapping("/{id}")
    public Result<Category> update(@PathVariable("id") Integer id, @Valid @RequestBody CategoryForm form, BindingResult bindingResult) {
        if (bindingResult.hasErrors()) {
            return Result.bizFail(bindingResult.getFieldError() == null ? "参数错误" : bindingResult.getFieldError().getDefaultMessage());
        }
        Category category = new Category();
        category.setCategoryId(id);
        category.setCategoryName(form.getCategoryName());
        category.setParentId(form.getParentId());
        category.setDescription(form.getDescription());
        return Result.success(categoryService.update(category));
    }

    @PostMapping("/{id}/delete")
    public Result<Void> delete(@PathVariable("id") Integer id) {
        categoryService.delete(id);
        return Result.success(null);
    }
}
