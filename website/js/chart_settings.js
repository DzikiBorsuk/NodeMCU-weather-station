$(function () {

    $('.change-interval').on('click',function (event) {
        let element = $(this);

        if(!element.hasClass('btn-active'))
        {
            $('.btn-active').removeClass('btn-active');
            element.addClass('btn-active');
            let interval = element.attr('id');
            // let canvas_id = $('canvas').attr('id');
            // let parent = $('canvas').parent();
            // parent.remove('canvas');
            // parent.append('<canvas></canvas>');
            // parent.children('canvas').attr(canvas_id);
            show_chart(interval,current_chart);
        }

    })
});